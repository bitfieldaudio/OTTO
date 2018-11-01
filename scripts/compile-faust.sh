#!/bin/bash

function compile {
    ARCH_DIR="./scripts"
    ARCH_FILE="faust-template.h"
    echo "Compiling $1"
    bn=$(basename $1)
    bn=${bn%.*}
    dir=$(dirname $1)
    classname=faust_${bn//-/_}

    faust -scal -lang ocpp -es 1 $1 -o "${dir}/${bn}.faust.hpp" -cn $classname -a $ARCH_DIR/$ARCH_FILE
}

if [[ $# == 1 ]]; then
    compile "$1"
else
    export -f compile

    echo "================================="
    echo "===== Compiling Faust files ====="
    echo "================================="
    echo ""
    find . -name "*.dsp" -type f -exec bash -c "compile '{}'" \;

    echo ""
    echo "===== Faust Compilation done ===="
fi
