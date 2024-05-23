#!/usr/bin/bash

if [ ! -d "Release/" ]
then
  mkdir Release
  cd Release/
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  cd ../
fi

clear && cd Release/ && make && cd bin/ && ./BIOHAZRD && cd ../../