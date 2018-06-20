
# Docker
The recommended way to run and develop for the OTTO is using the docker image. It includes all the required tools and dependencies, and should work out of the box on any linux machine.
```bash
cd OTTO
docker build . -t otto/topisani
```
Then to run the docker image
```bash
sh dockerrun.sh
```
This will build the source, and run OTTO, patchage and jack-keyboard.
The source will be mounted into docker from the current directory, so the image will not need to be rebuilt when the source is updated.

## Faust in docker
Most of the DSP is done using [faust](http://faust.grame.fr), which is preinstalled in the docker image. If you change any of the `.dsp` files, you will need to compile them by running
```bash
sh dockerrun.sh ./compile-faust.sh
```
If you are'nt using the docker image, check the manual faust section bellow.

## Pulseaudio
If you are using pulseaudio, you may have to pause it while running the docker container. This means you won't hear any sound from other applications.
To automatically suspend pulseaudio and restart it when OTTO closes, run the container like this:
```bash
pasuspender -- sh dockerrun.sh
```
# Manual Installation  
Install the dependencies. For Debian 9+/Ubuntu 16.10+, this should do the trick
```bash
apt install jackd\
    cmake\
    gcc\
    g++\
    pkg-config\
    libglfw3-dev\
    libedit-dev\
    libjack-jackd2-dev\
    libgles2-mesa-dev -y
```
**NOTE:** On Debian 8-/Ubuntu 16.04-, you will get errors about missing openGL files, and i have no idea why. Either use the docker image, upgrade your system, or try installing GLFW 3.2 from source.

I recommend also installing `patchage` and `jack-keyboard`, but they are in no way required.

With this set up, you can build & run the OTTO with
```
cmake .
make -j4
bin/tapedeck
```
or with the provided `install.sh` script.

It should be possible to get the OTTO running on Windows/Mac too, but for now you are on your own with that. If you do succeed in doing it, we'd apreciate a guide added to this README

## Manual Faust
If you change the `.dsp` files, you will need faust to compile them.
It is very important that you use the correct version, which currently is `0.9.104`. To install that, run the following commands:
```bash
git clone https://github.com/grame-cncm/faust
cd faust
git checkout 24db8d98e63aa8a119ffc601bf6aeec3e33e7a86
make
sudo make install
```
Once you have faust installed, verify that the `faust` command uses the correct version. You should see something like this:
```bash
$ faust --version
FAUST, DSP to C++ compiler, Version 0.9.104
Copyright (C) 2002-2017, GRAME - Centre National de Creation Musicale. All rights reserved. 
```

Then, make the apropriate changes in the `.dsp` files, and compile them by running
```
sh compile-faust.sh
```
faust especially is a lot easier to use with the docker image, even if you are running everything else outside it.

