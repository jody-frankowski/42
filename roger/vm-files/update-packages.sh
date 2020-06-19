#!/bin/bash

# This script is set to run in the background so as not to block the vm startup.
{
    set -ex

    export PATH="/run/current-system/profile/bin/:/run/current-system/profile/sbin/"

    # Use the lock so that guix pull doesn't complain:
    # 'guix pull: error: profile /var/guix/profiles/per-user/root/current-guix is locked by another process'
    # The lock isn't atomic but it should be good enough.
    while [ -f /tmp/update-packages.lock ]
    do
        sleep 1
    done
    touch /tmp/update-packages.lock

    # Hack to avoid the following problem:
    # Migrating profile generations to '/var/guix/profiles/per-user/root'...
    # guix pull: error: symlink: File exists: "/var/guix/profiles/per-user/root/current-guix"
    [ -L /var/guix/profiles/per-user/root/current-guix ] && rm -f /var/guix/profiles/per-user/root/current-guix

    if ! guix pull
    then
        echo "Another 'guix pull' may be already running."
    fi
    guix package -u

    rm /tmp/update-packages.lock
    echo "Updates finished."
} >> /var/log/update_script.log 2>&1 &
