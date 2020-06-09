#!/bin/sh
rm -rf /tmp/capstone
mkdir -p /tmp/capstone/src
cd /tmp/capstone/src
git clone --single-branch --branch release https://github.com/shristipradhan/capstone.git
cd capstone
mkdir -p  ../build
cd ../build
cmake ../capstone
make -j$(nproc)
./HotDogNCoke
