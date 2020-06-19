#!/bin/bash

set -euo pipefail

if [ $# -ne 1 ] ; then
    echo "Usage: $0 OUTGOING_INTERFACE_NAME"
    echo "OUTGOING_INTERFACE_NAME: An interface that is connected to the Internet/WAN."
    exit 1
fi

### SSH Keys Setup
if [ ! -f user-private-key ] || [ ! -f vm-files/user.pub ]
then
    ssk-keygen -f key -N ""
    mv -f key user-private-key
    mv -f key.pub vm-files/user.pub
fi

### Firewall Setup
[ -d libbpf ] || git clone --depth 1 https://github.com/libbpf/libbpf
[ -d libbpf/bpf ] || mv libbpf/src libbpf/bpf
clang -O2 -target bpf -c vm-files/firewall.c -o vm-files/firewall.o -I libbpf/ -Wall -Werror

### Image Setup
if [ ! -f roger.img ]
then
   set +e
   output="$(guix system vm-image --image-size=8G roger-vm.scm 2>&1)"
   if [ $? -ne 0 ]
   then
       echo "Failed to build the roger VM."
       echo "${output}"
       exit 1
   fi
   set -e

   image=$(echo "${output}" | tail -n1)
   cp "${image}" roger.img
   chmod u+w roger.img
   guestfish -a roger.img <<EOF
run
resize2fs-size /dev/sda1 4200M
EOF
   cp -f roger.img roger-new.img
   virt-resize --resize /dev/sda1=4.2G roger.img roger-new.img > /dev/null
   mv -f roger-new.img roger.img
fi

### Network Setup
outgoing_interface="$1"
netns=roger

(sudo ip netns list | grep "^${netns} " > /dev/null) && sudo ip netns del "${netns}" && sudo ip link del dev veth-default
sudo ip netns add "${netns}"

sudo ip netns exec "${netns}" ip tuntap add mode tap virt-pub-tap1  user "${USER}"
sudo ip netns exec "${netns}" ip tuntap add mode tap virt-pub-tap2  user "${USER}"
sudo ip netns exec "${netns}" ip tuntap add mode tap virt-priv-tap1 user "${USER}"
sudo ip netns exec "${netns}" ip tuntap add mode tap virt-priv-tap2 user "${USER}"
sudo ip netns exec "${netns}" ip link set virt-pub-tap1  up
sudo ip netns exec "${netns}" ip link set virt-pub-tap2  up
sudo ip netns exec "${netns}" ip link set virt-priv-tap1 up
sudo ip netns exec "${netns}" ip link set virt-priv-tap2 up

sudo ip netns exec "${netns}" ip link add br-pub  type bridge
sudo ip netns exec "${netns}" ip link add br-priv type bridge
sudo ip netns exec "${netns}" ip link set br-pub  up
sudo ip netns exec "${netns}" ip link set br-priv up

sudo ip netns exec "${netns}" ip link set virt-pub-tap1  master br-pub
sudo ip netns exec "${netns}" ip link set virt-pub-tap2  master br-pub
sudo ip netns exec "${netns}" ip link set virt-priv-tap1 master br-priv
sudo ip netns exec "${netns}" ip link set virt-priv-tap2 master br-priv

sudo ip link add veth-default type veth peer name veth-"${netns}"
sudo ip link set veth-"${netns}" netns "${netns}"
sudo ip netns exec "${netns}" ip link set veth-"${netns}" master br-pub
sudo ip addr add dev veth-default 172.16.0.1/24
sudo ip link set veth-default up
sudo ip netns exec "${netns}" ip link set veth-"${netns}" up

sudo iptables -F
sudo iptables -t nat -F
sudo iptables -t nat -A POSTROUTING -o "${outgoing_interface}" -j MASQUERADE
sudo iptables -A FORWARD -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
sudo iptables -A FORWARD -i veth-default -o "${outgoing_interface}" -j ACCEPT
# Drop traffic to broadcast address. If we don't, there is a high chance that
# the host will be "scan banned" by the vm.
sudo iptables -A OUTPUT -d 172.16.0.255/32 -j DROP

### Test VM Startup
./start-test-vm.sh &

### Roger VM Startup
mac1="52:54:00:00:00:01"
mac2="52:54:00:00:00:02"

# We use e1000 instead of virtio-pci-net because loading the xdp program threw
# this error:
# Error: virtio_net: Too few free TX rings available.
sudo ip netns exec "${netns}" \
     su "${USER}" -c \
     "qemu-system-x86_64 -cpu host -smp 4 -enable-kvm -no-reboot -object rng-random,filename=/dev/urandom,id=guixsd-vm-rng -device virtio-rng-pci,rng=guixsd-vm-rng -drive file=roger.img,if=virtio,cache=writeback,werror=report -m 2048 -nographic -serial none -monitor none \
           -nic tap,model=e1000,ifname=virt-pub-tap1,script=no,downscript=no,vhost=on,mac=\"${mac1}\" \
           -nic tap,model=e1000,ifname=virt-priv-tap1,script=no,downscript=no,vhost=on,mac=\"${mac2}\"" &

sleep 5
if ps -p $! > /dev/null
then
    echo "Roger VM successfully started."
    wait $!
else
    echo "Roger VM failed to start."
fi
