@ECHO OFF
git submodule update --recursive --remote
mkdir build
cmake  -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B .\build
cd build
ninja
