#!/bin/sh

set -euxo pipefail

export PATH="/run/current-system/profile/bin/:/run/current-system/profile/sbin/"

events=$(ausearch -k monitor-crontab -ts yesterday 00:00:00 -te yesterday 23:59:59 2>/dev/null)

if [ $? -eq 0 ]
then
    echo "${events}" | sendmail root
fi
