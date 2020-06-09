#!/bin/sh
rm -rf ~/capstone
mkdir -p ~/capstone/src
cd ~/capstone/src
git clone --single-branch --branch release https://github.com/shristipradhan/capstone.git
cd capstone
mkdir -p  ../build
cd ../build
cmake ../capstone
make -j$(nproc)
./HotDogNCoke
