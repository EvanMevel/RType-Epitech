#!/bin/bash
set -e
git submodule update --init --recursive

if [ ! -d "build" ]
then
    mkdir build
fi

cmake  -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./build
cd build
ninja
cd ..
