[private]
@default:
  just --list

setup:
  cmake -H. -Bbuild

build target="":
  test -d build || just setup
  cmake --build build -- {{target}}

run *args: 
  just build otto_exec && build/bin/otto -e {{args}}
  
gdb *args: 
  just build otto_exec && gdb --args build/bin/otto -e {{args}}
  
