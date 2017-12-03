#!/bin/bash

cd build
make clean
cd ..

./autogen.sh
cd build
../configure
make
cd ..
