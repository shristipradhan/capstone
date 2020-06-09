#!/bin/sh
rm -rf ~/capstone
mkdir -p ~/capstone/src
cd ~/capstone/src
git clone --single-branch --branch demo-ready https://github.com/shristipradhan/capstone.git
cd capstone
mkdir -p  build
cd build
cmake clean
cmake -D ..
make -j$(nproc)
./DisplayImage
