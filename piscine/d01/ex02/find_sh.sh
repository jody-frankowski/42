#!/bin/sh

find . -name "*.sh" -type f | sed 's@./@@' | sed 's@.sh$@@' | xargs basename
