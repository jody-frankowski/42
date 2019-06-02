#!/bin/sh

ldapsearch | grep -i 'sn:.*bon.*' | wc -l | tr -d ' '
