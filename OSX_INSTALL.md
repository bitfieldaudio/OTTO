# Installation on Mac OS Sierra (10.12)

---

Install **Homebrew** (if not already installed)
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

Install build tools: **LLVM**, **GCC**, **CMAKE**, and **GIT**
```
brew install llvm gcc cmake git
```

## Verify Installation (Optional)

These not necessary but useful if you want to verify the above installation was successful.

```which clang``` should be ```/usr/local/opt/llvm/bin/clang```

```which clang++``` should be ```/usr/local/opt/llvm/bin/clang++```

```which gcc-7``` should be ```/usr/local/bin/gcc-7```

```which cmake``` should be ```/usr/local/bin/cmake```

## Add Build Tools to Your Environment

Temporarily add build tools to your environment (for the current terminal session)
```
export PATH="/usr/local/opt/llvm/bin:$PATH" && export CC=clang && export CXX=clang++
```

Permanently add build tools to your environment
```
echo 'export PATH="/usr/local/opt/llvm/bin:$PATH" && export CC=clang && export CXX=clang++' >> ~/.bash_profile
```

## Set Build Flags

```
export CXXFLAGS=$(./flags.sh cxx) && export LDFLAGS=$(./flags.sh ld)
```

## Checkout TOP1

```
git clone https://github.com/topisani/TOP-1.git && cd ./TOP-1
```

## Execute Build

```
./build.sh
```
 
