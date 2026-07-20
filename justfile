[private]
@default:
  just --list

setup:
  cmake -H. -Bbuild -DOTTO_BOARD=desktop -DOTTO_USE_LIBCXX=ON -DOTTO_BUILD_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -Wno-dev

build target="":
  test -d build || just setup
  cmake --build build -- {{target}}

run *args:
  just build otto_exec && build/bin/otto -e {{args}}

# macOS desktop (speakers or -c ottoconf.mac.json for BlackHole)
run-mac *args:
  just build otto_exec && build/bin/otto -e {{args}}

bundle-mac:
  just build otto_exec
  bash scripts/macos/bundle-app.sh

gdb *args:
  just build otto_exec && gdb --args build/bin/otto -e {{args}}
 
