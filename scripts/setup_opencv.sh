#!/bin/sh

mkdir -p ~/opencv_ws/src
cd ~/opencv_ws/src
git clone --branch 4.3.0 https://github.com/opencv/opencv.git
git clone --branch 4.3.0 https://github.com/opencv/opencv_contrib.git
git clone --branch 4.3.0 https://github.com/opencv/opencv_extra.git
cd opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules/  BUILD_DOCS BUILD_EXAMPLES OPENCV_ENABLE_NONFREE ..
make -j$(nproc)
sudo make install
