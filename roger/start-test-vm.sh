#!/bin/bash

set -euo pipefail

set +e
output="$(guix system vm test-vm.scm 2>&1)"
if [ $? -ne 0 ]
then
    echo "Failed to build the test VM."
    echo "${output}"
    exit 1
fi
set -e

script=$(echo "${output}" | tail -n1)
args=$(cat $script | tail -n1 | awk '{print $9, $10}')
netns=roger

mac1="52:54:00:00:00:03"
mac2="52:54:00:00:00:04"

sudo ip netns exec "${netns}" \
     su "${USER}" -c \
     "${script} -cpu host -smp 4 -nographic -serial none -monitor none \
          -nic tap,model=virtio-net-pci,ifname=virt-pub-tap2,script=no,downscript=no,vhost=on,mac=\"${mac1}\" \
          -nic tap,model=virtio-net-pci,ifname=virt-priv-tap2,script=no,downscript=no,vhost=on,mac=\"${mac2}\"" &

sleep 5
if ps -p $! > /dev/null
then
    echo "Test VM successfully started."
else
    echo "Test VM failed to start."
fi
