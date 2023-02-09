#!/bin/bash
mkdir build
cmake  -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./build
cd build
ninja
