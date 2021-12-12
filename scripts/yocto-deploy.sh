#! /bin/bash

ip=$1; shift
binary=${1:-otto}; shift

builddir=oe-workdir/otto-core-1.0.0+git999

sshargs="-o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o LogLevel=ERROR"

_msg() {
  tput setaf 2
  tput bold
  echo -n "==> "
  tput sgr0
  tput bold
  # tput setaf 2
  echo "$@"
  tput sgr0
}

_err() {
  tput setaf 1
  tput bold
  echo -n "==> "
  tput sgr0
  tput bold
  echo "$@"
  tput sgr0
  return 1
}

_fail() {
  _err "$@"
  exit 1
}

_msg Compiling OTTO core through yocto
bitbake -c do_compile otto-core  || _fail "Failed to compile, will not deploy"
_msg "Remounting rootfs read/write"
ssh $sshargs root@$ip mount -o remount,rw /dev/root /
_msg "Stopping OTTO core"
ssh $sshargs root@$ip /etc/init.d/otto-core.sh stop
_msg "Deploying..."
scp $sshargs $builddir/bin/$binary root@$ip:/home/root/otto/bin/$binary
_msg "Remounting rootfs readonly"
ssh $sshargs root@$ip mount -o remount,ro /dev/root /
# _msg "Starting OTTO core"
# ssh $sshargs root@$ip sh -c "cd /data; /home/root/otto/bin/$binary"
_msg "Done!"

