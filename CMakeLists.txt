cmake_minimum_required(VERSION 3.3)
project(bbb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ftemplate-backtrace-limit=0 -pthread")

set(SOURCE_FILES tests/main.cpp)

include_directories(.)
add_executable(tests ${SOURCE_FILES})