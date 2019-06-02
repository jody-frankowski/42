#!/bin/sh

cat /etc/passwd | grep -v '^#' | awk 'NR % 2 == 0 { print }' | cut -d':' -f1 | rev | sort -r | sed -n "${FT_LINE1},${FT_LINE2}p" | xargs echo | sed 's/ /, /g' | tr '\n' '.'
