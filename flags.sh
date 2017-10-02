#!/usr/bin/env bash

function realpath () {
    echo $(cd "$(dirname "$1")"; pwd)/$(basename "$1")
}

function gccPath () {
    echo $(cd $(dirname $(which gcc-7)) && echo $(dirname $(realpath $(readlink gcc-7))));
}

function cxxFlags () {
    echo "-nostdinc++ -std=gnu++1z"
    echo | g++-7 -Wp,-v -x c++ - -fsyntax-only 2>&1 | grep "^[[:space:]]" | while read path; do
        echo "-I"$(realpath $path)" "
    done | tr -d '\n';
}

function ldFlags () {
    echo "-L/usr/local/Cellar/gcc/7.2.0/lib/gcc/7/"
}

if [ "$1" == "cxx" ]
    then echo $(cxxFlags);
fi

if [ "$1" == "ld" ]
    then echo $(ldFlags);
fi