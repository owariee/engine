#!/usr/bin/env bash
mkdir build-linux
cd build-linux
cmake ..
make
cd ..

mkdir build-windows
cd build-windows
cmake -DCMAKE_TOOLCHAIN_FILE=../externals/mingw-w64/mingw-w64-x86_64.cmake ..
make
