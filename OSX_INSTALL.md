# Installation using HomeBrew on Mac OS Sierra (10.12)

---

Install **Xcode Tools** (if not already installed)
```
xcode-select --install
```

Install **Homebrew** (if not already installed)
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

Install build tools: **LLVM**, **GCC**, and **CMAKE**
```
brew install llvm gcc cmake
```

Temporarily add build tools to your path (for the current terminal session)
```
export PATH="/usr/local/opt/llvm/bin:/usr/local/Cellar/gcc/7.2.0/bin:$PATH"
```

Permanently add build tools to your path
```
echo 'export PATH="/usr/local/opt/llvm/bin:$PATH"' >> ~/.bash_profile
```

## Verify Installation (Optional)

These following steps are not necessary but useful if you want to verify the above installation was successful.

```which clang``` should be ```/usr/local/opt/llvm/bin/clang```

```which clang++``` should be ```/usr/local/opt/llvm/bin/clang++```

```which gcc-7``` should be ```/usr/local/bin/gcc-7```

```which cmake``` should be ```/usr/local/bin/cmake```

