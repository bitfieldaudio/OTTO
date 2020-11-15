#!/bin/sh
# Ensure that the parent directory of the imput exists

mkdir -p "$1"
rm -rf "$1"
exit 0
