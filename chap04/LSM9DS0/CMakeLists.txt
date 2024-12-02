cmake_minimum_required(VERSION 3.3)
project(LSM9DS0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp lsm9ds0.cpp lsm9ds0.h)
add_executable(LSM9DS0 ${SOURCE_FILES})