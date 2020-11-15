#!/bin/sh
# Ensure that the parent directory of the imput exists

test -e "$1" || mkdir -p "$1"
test -d "$1" && rmdir "$1"
exit 0
