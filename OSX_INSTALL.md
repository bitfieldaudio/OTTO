# Installation on Mac OS Sierra (10.12)

Install Homebrew if not already installed
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

Install lzip
```
brew install lzip
```

https://solarianprogrammer.com/2017/05/21/compiling-gcc-macos/

1. Download GCC 7.2 from mirror of your choice: https://gcc.gnu.org/mirrors.html
    * http://mirrors.concertpass.com/gcc/releases/gcc-7.2.0/gcc-7.2.0.tar.xz
1. Download mpc 1.0.3
    * ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz
1. Download mpfr 3.1.6
    * http://www.mpfr.org/mpfr-current/mpfr-3.1.6.tar.gz
1. Download gmp 6.1.2
    * https://gmplib.org/download/gmp/gmp-6.1.2.tar.lz

Decompress Downloads

```
lzip -cd gmp-6.1.2.tar.lz | tar xopf -
```

```
gunzip -c gcc-7.2.0.tar.gz | tar xopf -
gunzip -c mpc-1.0.3.tar.gz | tar xopf -
gunzip -c mpfr-3.1.6.tar.gz | tar xopf -

```


