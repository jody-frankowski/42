#!/bin/sh

ldapsearch "uid=z*" 2>&1 | grep -v '^SASL' | grep "^cn:" | sort -rf
