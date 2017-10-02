#!/usr/bin/env bash


function realpath () {
    echo $(cd "$(dirname "$1")"; pwd)/$(basename "$1")
}

function gccPath () {
    echo $(cd $(dirname $(which gcc-7)) && echo $(dirname $(realpath $(readlink gcc-7))));
}

function cxxFlags () {
    echo | g++-7 -Wp,-v -x c++ - -fsyntax-only 2>&1 | grep "^[[:space:]]" | while read path; do
        echo "-I"$(realpath $path)" "
    done | tr -d '\n';
    echo "-nostdinc++ "
    echo $(ldFlags)
}

function ldFlags () {
    echo "
    /usr/local/Cellar/gcc/7.2.0/lib/gcc/7/libstdc++.a
    /usr/local/Cellar/gcc/7.2.0/lib/gcc/7/libstdc++fs.a
    /usr/local/Cellar/gcc/7.2.0/lib/gcc/7/libatomic.a"
}

if [ "$1" == "cxx" ]
    then echo $(cxxFlags);
fi

if [ "$1" == "ld" ]
    then echo $(ldFlags);
fi