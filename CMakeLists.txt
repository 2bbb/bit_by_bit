cmake_minimum_required(VERSION 3.3)
project(bit_by_bit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES main.cpp src/thread_utils.hpp src/constants.hpp src/math_utils.hpp)

include_directories(src)
add_executable(bit_by_bit ${SOURCE_FILES})