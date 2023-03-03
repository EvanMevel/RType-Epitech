#!/bin/bash
set -e
git submodule update --init --recursive
mkdir build
cmake  -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./build
cd build
ninja
cd ..
