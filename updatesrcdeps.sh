#!/bin/bash

cd src/

echo "target_sources(BIOHAZRD PRIVATE" > CMakeLists.txt

for fname in $(find . -maxdepth 4 -type f)
    do 
        if [ ${fname##*\.} == "cpp" ];
        then
            echo ${fname} >> CMakeLists.txt 
        fi 
done

echo ")" >> CMakeLists.txt
