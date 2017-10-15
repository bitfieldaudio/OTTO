#<cldoc:installing>

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
