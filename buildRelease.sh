#!/bin/bash

./build.sh

if [ ! -d "releaseLinux" ]
then
    mkdir releaseLinux
fi

mkdir client
mkdir server
mkdir pong

cp -R Client/assets client/
cp build/Client/r-type-client client/
cp -R config client/

cp build/Pong/pong pong/
cp -R Pong/assets pong/

cp build/Server/r-type-server server/
cp -R config server/

zip releaseLinux/r-type-client.zip -r client/

zip releaseLinux/r-type-server.zip -r server/

zip releaseLinux/pong.zip -r pong/

rm -rf server/ pong/ client/
