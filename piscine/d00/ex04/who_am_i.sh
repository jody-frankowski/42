#!/bin/sh

ldapwhoami | cut -d ':' -f2-
