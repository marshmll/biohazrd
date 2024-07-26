#!/usr/bin/bash

if [ ! -d "Release/" ]
then
    mkdir Release
    cd Release/
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cd ../
fi

rm -rf Release/bin/Assets/ Release/bin/Config/ Release/bin/Fonts/ Release/bin/Maps Release/bin/Shaders Release/bin/Logs
cp -r src/Assets/ Release/bin/
cp -r src/Config/ Release/bin/
cp -r src/Fonts/ Release/bin/
cp -r src/Maps/ Release/bin/
cp -r src/Shaders/ Release/bin/

clear
cd Release/ &&
make &&
cd bin/ &&
./BIOHAZRD &&
cd ../../

rm -rf src/Assets/ src/Config/ src/Fonts/ src/Maps/ src/Shaders src/Logs
cp -r Release/bin/Assets src/
cp -r Release/bin/Config src/
cp -r Release/bin/Fonts src/
cp -r Release/bin/Maps src/
cp -r Release/bin/Shaders src/
