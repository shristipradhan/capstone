#!/bin/sh
mkdir -p ~/capstone/src
cd ~/capstone/src
git clone https://github.com/shristipradhan/capstone.git
cd capstone
mkdir -p  build
cd build
cmake -D CMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
./DisplayImage
