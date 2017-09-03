#<cldoc:installing>

# In Ubuntu 16.04
This is the recommended version to run in a VM.

Install the dependencies:
```shell
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install git cmake pkg-config libjack-jackd2-dev jackd2 \
  libglfw3-dev libgles2-mesa-dev gcc-7 g++-7
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 90
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 90
```
Confirm that `g++ --version` results in something like this:
```shell
g++ (Ubuntu 7.2.0-1ubuntu1~16.04) 7.2.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

Clone the repo:
```shell
git clone https://github.com/topisani/TOP-1
cd TOP-1
```

Build and Conquer:
```shell
cmake .
make
bin/top-1
```

`make` also compiles the tests. To run them:
```shell
bin/tests 
```
