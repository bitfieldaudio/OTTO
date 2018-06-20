#<cldoc:installing>

# On Raspbian Lite
The OTTO-prototype-1 runs on a Raspberry Pi-3. The following instructions run you through the process of getting OTTO to run on it.
## Prerequisites

- Flash Raspbian Lite on an SD card (e.g. with Etcher)
- Log in with default login: pi, password: raspberry
- Change the password with `sudo raspberry-config`
- Update the kernel with:
```bash
$ sudo rpi-update
$ sync
$ sudo reboot
```
- Update the packages with
```bash
$ sudo apt-get update && sudo apt-get upgrade
```

- Make sure your DAC is connected, and working. You can test it with 
```bash
$ speaker-test -c 2
```
Ideally, you should see *something similar to the example* when you run the two following commands:
```bash
$ aplay -l
**** List of PLAYBACK Hardware Devices **** 
card 0: Audio[Fe-Pi Audio], device 0: Fe-Pi HiFi sgtl5000-0 []
Subdevices: 1/1
Subdevice #0: subdevice #0

$ arecord -l
**** List of CAPTURE Hardware Devices ****
card 0: Audio[Fe-Pi Audio], device 0: Fe-Pi HiFi sgtl5000-0 []
Subdevices: 1/1 
Subdevice #0: subdevice #0
```


## 1. Installing clang6 from precompiled binaries

```bash
$ mkdir dl && cd dl
$ wget http://releases.llvm.org/6.0.0/clang+llvm-6.0.0-armv7a-linux-gnueabihf.tar.xz
$ tar xvf clang*
$ cd clang*
$ sudo cp -Rv * /usr/local/
$ echo 'export CXX=clang++ CC=clang' >> ~/.bashrc
```

## 2. Installing cmake 3.12.0 from the sources

```bash
$ cd ~/dl
$ wget https://cmake.org/files/v3.12/cmake-3.12.0-rc1.tar.gz
$ tar xvf cmake*
$ cd cmake*
$ ./bootstrap
$ sudo make
$ sudo make install
```

PLEASE NOTE: `./boostrap` and building on the Raspberry Pi takes a looooong time, so if you're feeling lucky, you can run the following, and go for a walk:
```bash
$ ./bootstrap && sudo make && sudo make install
```

## 3. Installing Jack from the sources

The default jack binary, available in the apt repos, requires dbus, which only runs in an x server. In order to use jack, we need to recompile it from the sources.

```bash
$ sudo apt-get install libasound2-dev libjack-jackd2-dev
$ git clone git://github.com/jackaudio/jack2.git 
$ cd jack2
$ ./waf configure --alsa --prefix=/usr --libdir=/usr/lib/arm-linux-gnueabihf
$ ./waf
$ sudo ./waf install
$ sudo rm /usr/bin/jackdbus
```

## 4. Updating man to include jack's and clang's man pages
```bash
$ sudo mandb
```

// TODO: find how to install cmake's man pages as well

## 5. Cloning the OTTO repo and building

Note: you may have to [create ssh keys](https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/) and [add them to your github account](https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/)

```bash
$ git clone git@github.com:topisani/OTTO.git
$ cd OTTO
$ git checkout develop-topisani
$ rm external/src/gl3w.c
$ cmake -DOTTO_BOARD=rpi-proto-1 -DOTTO_USE_LIBCXX=ON .
$ make
```
## 6. Launching OTTO
```bash
$ boards/rpi-proto-1/doc/jackstart.sh
$ bin/otto
```



# In Ubuntu 16.04
This is the recommended version to run in a VM.

Install the dependencies:
```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install git cmake pkg-config libjack-jackd2-dev jackd2 \
  libglfw3-dev libgles2-mesa-dev gcc-7 g++-7
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 90
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 90
```
Confirm that `g++ --version` results in something like this:
```bash
g++ (Ubuntu 7.2.0-1ubuntu1~16.04) 7.2.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

Clone the repo:
```bash
git clone https://github.com/topisani/OTTO
cd OTTO
```

Build and Conquer:
```bash
cmake .
make
bin/otto
```

`make` also compiles the tests. To run them:
```bash
bin/tests 
```
