cmake_minimum_required(VERSION 2.8)
project( DisplayImage )

INCLUDE_DIRECTORIES( PROJECT_SOURCE_DIR )
find_package( OpenCV REQUIRED )

add_executable( DisplayImage src/DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
