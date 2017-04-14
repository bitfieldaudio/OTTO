#!/bin/bash

function compile {
    ARCH_DIR="./faust"
    ARCH_FILE="template.h"
    echo "Compiling $1"
    bn=$(basename $1)
    bn=${bn%.*}
    dir=$(dirname $1)

    faust $1 -o "${dir}/${bn}.faust.h" -cn $bn -A $ARCH_DIR -a $ARCH_FILE
}

export -f compile

echo "================================="
echo "===== Compiling Faust files ====="
echo "================================="
echo ""
find . -name "*.dsp" -type f -exec bash -c "compile '{}'" \;

echo ""
echo "===== Faust Compilation done ===="
