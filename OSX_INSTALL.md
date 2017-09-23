# Installation on Mac OS Sierra (10.12)

Install Xcode Tools
```
xcode-select --install
```

Install Homebrew if not already installed
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

Install lzip
```
brew install lzip
```

https://solarianprogrammer.com/2017/05/21/compiling-gcc-macos/

### Download 

Save the downloads into a folder of your choosing.  We will use ```~/dev/tools```

1. Download GCC 7.2 from mirror of your choice: https://gcc.gnu.org/mirrors.html
    * http://mirrors.concertpass.com/gcc/releases/gcc-7.2.0/gcc-7.2.0.tar.xz
1. Download mpc 1.0.3
    * ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz
1. Download mpfr 3.1.6
    * http://www.mpfr.org/mpfr-current/mpfr-3.1.6.tar.gz
1. Download gmp 6.1.2
    * https://gmplib.org/download/gmp/gmp-6.1.2.tar.lz
1. Download isl 0.16.1
    * ftp://gcc.gnu.org/pub/gcc/infrastructure/isl-0.16.1.tar.bz2
1. Download cmake 3.9.3
    * https://cmake.org/files/v3.9/cmake-3.9.3-Darwin-x86_64.dmg
1. Download jackOSX 0.92_b3
    * https://github.com/jackaudio/jackaudio.github.com/releases/download/1.9.11/JackOSX.0.92_b3.zip

### Decompress

```
cd ~/dev/tools
lzip -cd gmp-6.1.2.tar.lz | tar xopf -
gunzip -c gcc-7.2.0.tar.gz | tar xopf -
gunzip -c mpc-1.0.3.tar.gz | tar xopf -
gunzip -c mpfr-3.1.6.tar.gz | tar xopf -
bunzip2 -cd isl-0.16.1.tar.bz2 | tar xopf -
```

You should now have a folder structure like this:

```
dev/
└── tools/
    ├── gcc-7.2.0/
    ├── gmp-6.1.2/
    ├── isl-0.16.1/
    ├── mpc-1.0.3/
    └── mpfr-3.1.6/
```

### Create /usr/local/gcc-7.2

> This may not be necessary.

```
sudo mkdir /usr/local/gcc-7.2
```

### Compile GMP

```
cd gmp* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --enable-cxx
make -j 4 && sudo make install
rm -rf ./build
```

### Compile MPFR

```
cd ../../ && cd mpfr* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --with-gmp=/usr/local/gcc-7.2
make -j 4 && sudo make install
rm -rf ./build
```

### Compile MPC

```
cd ../../ && cd mpc* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --with-gmp=/usr/local/gcc-7.2 --with-mpfr=/usr/local/gcc-7.2
make -j 4 && sudo make install
rm -rf ./build
```

### Compile Graphite Optimizations Lib

```
cd ../../ && cd isl* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --with-gmp-prefix=/usr/local/gcc-7.2
make -j 4 && sudo make install
rm -rf ./build
```

### Compile GCC

> This will take a quite a while and turn your computer into a space heater.

```
cd ../../ && cd gcc* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --enable-checking=release --with-gmp=/usr/local/gcc-7.2 --with-mpfr=/usr/local/gcc-7.2 --with-mpc=/usr/local/gcc-7.2 --enable-languages=c,c++ --with-isl=/usr/local/gcc-7.2 --program-suffix=-7.2
make -j 4 && sudo make install
rm -rf ./build
```

### Place GCC7.2 In Your Path

```
export PATH=/usr/local/gcc-7.2/bin:$PATH
```

### Install CMake

Open ```cmake-3.9.3-Darwin-x86_64.dmg``` from Finder and follow installation instructions.

### Install JackOSX

Decompress ```JackOSX.0.92_b3.zip``` from Finder, open the resulting package, and follow installation instructions.

