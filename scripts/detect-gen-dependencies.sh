#!/bin/bash

src_dir=$1; shift
file=$1; shift
out_dir=$1; shift

grep -Po '#include ["<]\K(.*)(?=\.gen\.hpp[">])' "$src_dir/$file" | while read basename; do
 [ -e "$src_dir/$basename.hpp" ] && echo -n "$src_dir/$basename.gen.hpp;"
done

echo -n "$src_dir/$file"

grep -F "[[otto::reflect]]" "$src_dir/$file" >> /dev/null || exit 1
