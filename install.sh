#!bin/bash
# This is just a shortcut for the container
# to compile the program the first time it's launched

cd /top-1
cmake .
make -j4
