cmake_minimum_required(VERSION 2.8)
project( HotDogNCoke )

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

INCLUDE_DIRECTORIES( PROJECT_SOURCE_DIR )
find_package( OpenCV REQUIRED )

add_executable( HotDogNCoke
	src/template_matcher.cpp
	src/HotDogNCoke.cpp )

target_link_libraries( HotDogNCoke ${OpenCV_LIBS} )
