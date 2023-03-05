#!/bin/bash
./build.sh

if [ ! -d "/path/to/dir" ]
then
    mkdir releaseLinux
fi

zip -r releaseLinux/r-type-client.zip .\build\Client\r-type-client.exe .\Client\assets .\config

zip -r releaseLinux/r-type-server.zip .\build\Server\r-type-server.exe .\config

zip -r releaseLinux/pong.zip .\build\Pong\pong.exe .\Pong\assets
