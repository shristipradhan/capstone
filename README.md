# HotDogNCoke

![HotDogNCoke](HotDogNCoke.png)

In this project, we demonstrate an HotDogNCoke detector that can detect if there is Coke and/orf HotDog in an Image.

We use sample data from google image search to create our labelled datasets of Coke and HotDog.
These samples are in `resources/train/hotdog` and `resources/train/coke`
Based on these templates, we use to apply a convolutional filter on test dataset.

# Build Instructions

```
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
```

# Requirements

This project requires `opencv` ,	`opencv_contrib` and `opencv_extra` packages. This project was built on stable release `4.3.0`. So, please note to use the release.

```
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
```

# Scripts

There are handy scripts to help automate setup of opencv and this package in `scripts/install.sh` and `scripts/setup_opencv.sh`

Use as is! 
