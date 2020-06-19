#!/bin/bash

set -euo pipefail

PORT="9595"
USER="user"
HOST_ROGER_VM="172.16.0.2"
HOST_TEST_VM="172.16.0.3"

SUDO_CMD="echo 'test' | sudo -S"

SSH_NO_KEY_CHECKING="-o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no"

execute-on-roger-vm ()
{
    ssh ${SSH_NO_KEY_CHECKING} -i user-private-key -p "${PORT}" "${USER}"@"${HOST_ROGER_VM}" "$@"
}
execute-on-test-vm ()
{
    ssh ${SSH_NO_KEY_CHECKING} -i user-private-key -p "${PORT}" "${USER}"@"${HOST_TEST_VM}" "$@"
}

error ()
{
    echo "Test failed: $@"
    exit 1
}

# Wait for both vm to be reachable
echo "Waiting for the VMs to be reachable."
while ! (execute-on-roger-vm true 2>/dev/null && execute-on-test-vm true 2>/dev/null)
do
    sleep 1
done

echo "The VMs are now reachable."
echo "Executing tests."

# A disk size of 8 GB.
if [ "$(execute-on-roger-vm "lsblk --nodeps --raw --noheading --output SIZE /dev/vda")" != "8G" ]
then
    error "The main disk isn't 8GB big."
fi

# Have at least one 4.2 GB partition.
if [ "$(execute-on-roger-vm "lsblk --raw --noheading --output SIZE /dev/vda1")" != "4.2G" ]
then
    error "The main partition isn't 4.2GB big."
fi

# You must create a non-root user to connect to the machine and work.
if [ "$(execute-on-roger-vm "id")" != "uid=1000(${USER}) gid=998(users) groups=998(users),999(wheel)" ]
then
    error "Non-root user '${USER}' doesn't exist."
fi

# Use sudo, with this user, to be able to perform operation requiring special
# rights.
if [ "$(execute-on-roger-vm "${SUDO_CMD} id 2>/dev/null")" != "uid=0(root) gid=0(root) groups=0(root)" ]
then
    error "Non-root user '${USER}' doesn't have sudo rights."
fi

# We don’t want you to use the DHCP service of your machine. You’ve got
# to configure it to have a static IP and a Netmask in\30.
if [ "$(execute-on-roger-vm "ip a show ens3 | grep '172.16.0.2/30' | awk '{print \$2}'")" != "172.16.0.2/30" ]
then
    error "Main network interface doesn't have a /30 ip address."
fi

# You have to change the default port of the SSH service by the one of your
# choice.
if [ -n "$(execute-on-roger-vm "${SUDO_CMD} lsof -i :22 2>/dev/null")" ]
then
    error "A process is listening on port 22"
fi
if [ "$(execute-on-roger-vm "${SUDO_CMD} lsof -iTCP -sTCP:LISTEN -P -n 2>/dev/null" | grep '^sshd' | awk '{print $9}' | cut -d: -f2)" != "${PORT}" ]
then
    error "sshd isn't listening on ${PORT}"
fi

# SSH access HAS TO be done with publickeys.
# head -c -2 because ssh outputs CRLF with its error messages
if [ "$(ssh ${SSH_NO_KEY_CHECKING} \
            -o ControlPath=none \
            -o PreferredAuthentications=none \
            "${USER}"@"${HOST_ROGER_VM}" -p "${PORT}" "id" 2>&1 | \
            grep Permission | head -c -2)" \
         != "${USER}@${HOST_ROGER_VM}: Permission denied (publickey)." ]
then
    error "sshd doesn't allow only publickey authentication."
fi

# SSH root access SHOULD NOT
# be allowed directly, but with a user who can be root.
# head -c -2 because ssh outputs CRLF with its error messages
if [ "$(ssh ${SSH_NO_KEY_CHECKING} \
            root@"${HOST_ROGER_VM}" -p "${PORT}" "id" 2>&1 \
            | grep Permission | head -c -2)" \
         != "root@${HOST_ROGER_VM}: Permission denied (publickey)." ]
then
    error "sshd allows root user."
fi

# You have to set the rules of your firewall on your server only with the
# services used outside the VM.
# ssh "nc -l -p "
# Skipped because it is rather hard to test with the eBPF firewall.

# You have to set a DOS (Denial Of Service Attack) protection on your open ports
# of your VM.
set +e
execute-on-test-vm "dd if=/dev/zero bs=30000000 count=1 2>/dev/null | timeout 5 ncat 10.0.0.1 443 > /dev/null"
set -e
if execute-on-test-vm timeout 1 curl -s 10.0.0.1:443 > /dev/null
then
    error "Port 443 isn't DOS protected."
fi
sleep 31s
if ! execute-on-test-vm timeout 1 curl -s 10.0.0.1:443 > /dev/null
then
    error "The firewall hasn't unbanned us."
fi

# You have to set a protection against scans on your VM’s open ports
execute-on-test-vm nmap -sV -Pn -p 1-128 10.0.0.1 > /dev/null
if execute-on-test-vm timeout 1 curl -s 10.0.0.1:443 > /dev/null
then
    error "There is no scan protection."
fi
sleep 31s
if ! execute-on-test-vm timeout 1 curl -s 10.0.0.1:443 > /dev/null
then
    error "The firewall hasn't unbanned us."
fi

# Stop the services you don’t need for this project.
want=" + auditd
 + console-font-tty1
 + console-font-tty2
 + console-font-tty3
 + console-font-tty4
 + console-font-tty5
 + console-font-tty6
 + file-system-/dev/pts
 + file-system-/dev/shm
 + file-system-/gnu/store
 + file-systems
 + guix-daemon
 + loopback
 + mcron
 + networking
 + networking-ens3
 + networking-ens4
 + nginx
 + nscd
 + root
 + root-file-system
 + smtpd
 + ssh-daemon
 + syslogd
 + term-tty1
 + term-tty2
 + term-tty3
 + term-tty4
 + term-tty5
 + term-tty6
 + udev
 + urandom-seed
 + user-file-systems
 + user-processes
 + virtual-terminal"
if [ "$(execute-on-roger-vm "${SUDO_CMD} herd status 2>/dev/null " | grep '+')" != "${want}" ]
then
    error "Some unexpected services are started."
fi

# Create a script that updates all the sources of package, then your packages
# and which logs the whole in a file named /var/log/update_script.log. Create a
# scheduled task for this script once a week at 4AM and every time the machine
# reboots.
if ! execute-on-roger-vm 'ps aux' | grep update-packages.sh > /dev/null
then
    if ! execute-on-roger-vm "grep 'Updates finished.' /var/log/update_script.log > /dev/null"
    then
        error "The packages haven't been updated at boot."
    fi
fi
execute-on-roger-vm "${SUDO_CMD} rm -f /var/log/update_script.log 2>/dev/null"
execute-on-roger-vm "${SUDO_CMD} date -s 03:59 >/dev/null 2>&1"
execute-on-roger-vm "${SUDO_CMD} herd restart mcron > /dev/null 2>&1"
sleep 2m
if ! execute-on-roger-vm 'ps aux' | grep update-packages.sh > /dev/null
then
    if ! execute-on-roger-vm "grep 'Updates finished.' /var/log/update_script.log > /dev/null"
    then
        error "The packages haven't been updated at 4am."
    fi
fi

# Make a script to monitor changes of the /etc/crontab file and sends an email
# to root if it has been modified. Create a scheduled script task every day at
# midnight.
execute-on-roger-vm "${SUDO_CMD} touch /etc/crontab 2>/dev/null"
execute-on-roger-vm "${SUDO_CMD} date -s 23:59 >/dev/null 2>&1"
execute-on-roger-vm "${SUDO_CMD} herd restart mcron > /dev/null 2>&1"
sleep 2m
if [ -z "$(execute-on-roger-vm "${SUDO_CMD} cat /var/mail/root 2>/dev/null")" ]
then
    error "Changes to /etc/crontab were not detected."
fi

# You have to set a web server who should BE available on the VM’s IP or an host
# (init.login.com for exemple). About the packages of your web server, you can
# choose between Nginx and Apache. You have to set a self-signed SSL on all of
# your services.
if ! echo QUIT | openssl s_client -connect "${HOST_ROGER_VM}":443 2>&1 | grep 'self signed certificate' > /dev/null
then
    error "The web server doesn't use a self signed certificate."
fi
if ! curl -s -k https://"${HOST_ROGER_VM}" > /dev/null
then
    error "The web server doesn't work."
fi
git checkout website 2>/dev/null
./deploy.sh > /dev/null 2>&1
if ! curl -s -k https://"${HOST_ROGER_VM}" | grep '<title>Cat</title>' > /dev/null
then
    error "The website wasn't deployed properly."
fi

# Propose a functional solution for deployment automation.
git checkout website 2>/dev/null
echo test > website/index.html
./deploy.sh > /dev/null 2>&1
if [ "$(curl -s -k https://${HOST_ROGER_VM})" != "test" ]
then
    error "The deployment solution doesn't work."
fi
git checkout website 2>/dev/null

echo "All tests passed."
