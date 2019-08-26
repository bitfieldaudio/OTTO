# source this script to get the CMAKE env var
cmake_dir=cmake
cmake_bin=$cmake_dir/bin/cmake
cmake_url="https://cmake.org/files/v3.9/cmake-3.9.2-Linux-x86_64.sh"

# Work with travis cache
if [[ ! -f $cmake_bin ]]; then
    mkdir -p $cmake_dir
    wget $cmake_url -O $cmake_dir/install-cmake.sh
    chmod +x $cmake_dir/install-cmake.sh
    $cmake_dir/install-cmake.sh --prefix=$cmake_dir --exclude-subdir
fi

export CMAKE_INSTALL_PREFIX=$cmake_dir
export CMAKE=$cmake_bin
