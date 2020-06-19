#!/bin/bash

set -euxo pipefail

# Sleep one second so that we can never have two identical 'date -Iseconds`
# outputs. We should use a lock and a unique name mechanism, but this is
# simpler.
sleep 1

date="$(date -Iseconds)"
ssh_args="-o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -i user-private-key -o Port=9595"
remote="user@172.16.0.2"
sudo_cmd="echo 'test' | sudo -S"

# Could be a git clone, but for convenience it's a simple scp of a local directory
ssh ${ssh_args} "${remote}" "${sudo_cmd} mkdir -p /srv/http/roger-skyline.sh/"
scp -r ${ssh_args} website "${remote}":"${date}"
ssh ${ssh_args} "${remote}" "${sudo_cmd} mv ~user/${date} /srv/http/roger-skyline.sh/"
ssh ${ssh_args} "${remote}" "${sudo_cmd} chown -R nginx:nginx /srv/http/roger-skyline.sh/${date}"

# Atomically change the 'current' symlink
ssh ${ssh_args} "${remote}" "${sudo_cmd} sh -c 'ln -s /srv/http/roger-skyline.sh/${date} /srv/http/roger-skyline.sh/tmp && mv -f -T /srv/http/roger-skyline.sh/tmp /srv/http/roger-skyline.sh/current'"
