@ECHO OFF
mkdir build
cmake  -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B .\build
cd build
ninja
cd ..\
mkdir release
robocopy .\Client\assets release\assets /E
copy .\build\r-type-client.exe release\
powershell Compress-Archive -Force -Path ".\release\r-type-client.exe,.\release\assets" -DestinationPath ".\release\r-type-client.zip"
copy .\build\r-type-server.exe release\
DEL .\release\r-type-client.exe
@RD /S /Q .\release\assets