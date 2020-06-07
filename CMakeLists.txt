cmake_minimum_required(VERSION 2.8)
project( DisplayImage )

set(CMAKE_BUILD_TYPE Debug)

INCLUDE_DIRECTORIES( PROJECT_SOURCE_DIR )
find_package( OpenCV REQUIRED )

add_executable( DisplayImage src/DisplayImage.cpp src/Data.cpp)
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
