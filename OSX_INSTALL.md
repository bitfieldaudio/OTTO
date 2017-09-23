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

1. Download GCC 7.2 from mirror of your choice: https://gcc.gnu.org/mirrors.html
    * http://mirrors.concertpass.com/gcc/releases/gcc-7.2.0/gcc-7.2.0.tar.xz
1. Download mpc 1.0.3
    * ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz
1. Download mpfr 3.1.6
    * http://www.mpfr.org/mpfr-current/mpfr-3.1.6.tar.gz
1. Download gmp 6.1.2
    * https://gmplib.org/download/gmp/gmp-6.1.2.tar.lz
1. Download isl-0.16.1
    * ftp://gcc.gnu.org/pub/gcc/infrastructure/isl-0.16.1.tar.bz2

### Decompress

```
lzip -cd gmp-6.1.2.tar.lz | tar xopf -
gunzip -c gcc-7.2.0.tar.gz | tar xopf -
gunzip -c mpc-1.0.3.tar.gz | tar xopf -
gunzip -c mpfr-3.1.6.tar.gz | tar xopf -
bunzip2 -cd isl-0.16.1.tar.bz2 | tar xopf -
```

### Compile GMP

```
sudo mkdir /usr/local/gcc-7.2
cd gmp* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --enable-cxx
make -j 4 && sudo make install
```

### Compile MPFR

```
cd ../../ && cd mpfr* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --with-gmp=/usr/local/gcc-7.2
make -j 4 && sudo make install
```

### Compile MPC

```
cd ../../ && cd mpc* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --with-gmp=/usr/local/gcc-7.2 --with-mpfr=/usr/local/gcc-7.2
make -j 4 && sudo make install
```

### Compile Graphite Optimizations Lib

```
cd ../../ && cd isl* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --with-gmp-prefix=/usr/local/gcc-7.2
make -j 4 && sudo make install
```

### Compile GCC

> This will take a long time (hour+) and turn your computer into a heater.

```
cd ../../ && cd gcc* && mkdir build && cd build
../configure --prefix=/usr/local/gcc-7.2 --enable-checking=release --with-gmp=/usr/local/gcc-7.2 --with-mpfr=/usr/local/gcc-7.2 --with-mpc=/usr/local/gcc-7.2 --enable-languages=c,c++ --with-isl=/usr/local/gcc-7.2 --program-suffix=-7.2
make -j 4 && sudo make install
```
