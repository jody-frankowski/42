#!/bin/sh

{
    set -euxo pipefail

    export PATH="/run/current-system/profile/bin/:/run/current-system/profile/sbin/"

    CN="roger-skyline.sh"

    if [ -f "/etc/nginx/ssl/${CN}.key" ] && [ -f "/etc/nginx/ssl/${CN}.crt" ] ; then
        exit 0
    fi

    mkdir -p /etc/nginx/ssl
    cd /etc/nginx/ssl

    openssl req -nodes -newkey rsa:2048 -keyout "${CN}".key -out "${CN}".csr \
            -subj "/C=FR/L=Paris/O=Roger Skyline Corp/CN=roger-skyline.sh"

    openssl x509 -req -days 365 -in "${CN}".csr \
            -signkey "${CN}".key \
            -out "${CN}".crt
} >> /var/log/generate_certificate.log 2>&1
