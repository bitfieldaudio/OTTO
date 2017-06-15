#!bin/bash
# This is just a shortcut for the container
# to compile the program the first time it's launched

cmake .
make -j4

kbd() {
    sleep 2 && jack-keyboard -a TOP-1:midi_in
}
patchage &
kbd &
bin/tapedeck
