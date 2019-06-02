#!/bin/sh

ifconfig | grep -E 'ether ([a-f0-9]{2}:){5}[a-f0-9]{2}' | awk '{print $2}'
