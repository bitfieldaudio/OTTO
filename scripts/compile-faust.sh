#!/bin/bash

function compile_synth {
    ARCH_DIR="./scripts"
    ARCH_FILE="faust-template.h"
    echo "Compiling $1"
    bn=$(basename $1)
    bn=${bn%.*}
    dir=$(dirname $1)
    classname=faust_${bn//-/_}

    faust -scal -lang ocpp -es 1 $1 -o "${dir}/${bn}.faust.hpp" -cn $classname -a $ARCH_DIR/$ARCH_FILE
}

function compile_fx {
    ARCH_DIR="./scripts"
    ARCH_FILE="faust-template.h"
    echo "Compiling $1"
    bn=$(basename $1)
    bn=${bn%.*}
    dir=$(dirname $1)
    classname=faust_${bn//-/_}

    faust -vec -lang cpp $1 -o "${dir}/${bn}.faust.hpp" -cn $classname -a $ARCH_DIR/$ARCH_FILE
}

if [[ $# == 1 ]]; then
    compile_synth "$1"
else
    export -f compile_synth
    export -f compile_fx

    echo "================================="
    echo "===== Compiling Faust files ====="
    echo "================================="
    echo ""
    find . -wholename "./src/engines/synths/*.dsp" -type f -exec bash -c "compile_synth '{}'" \;
    echo ""
    find . -wholename "./src/engines/fx/*.dsp" -type f -exec bash -c "compile_fx '{}'" \;
    echo ""
    echo "===== Faust Compilation done ===="
fi
