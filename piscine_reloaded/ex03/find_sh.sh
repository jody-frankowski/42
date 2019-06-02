#!/bin/sh

find . -name "*.sh" -type f | xargs -n1 basename | sed 's@.sh$@@'
