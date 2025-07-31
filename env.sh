#!/bin/bash
# ARM GCC toolchain environment setup

export ARM_GCC_PATH="/usr/bin"
export PATH="$ARM_GCC_PATH:$PATH"
export CC="arm-none-eabi-gcc"
export CXX="arm-none-eabi-g++"
export AS="arm-none-eabi-as"
export CMAKE_TOOLCHAIN_FILE="../cmake/gcc-arm-none-eabi.cmake"
export CMAKE_BUILD_TYPE="Debug"
