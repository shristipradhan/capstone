#!/bin/sh
rm -rf ../../build
mkdir -p  ../../build
cd ../../build
cmake ../capstone
make clean
make -j$(nproc)
./HotDogNCoke
