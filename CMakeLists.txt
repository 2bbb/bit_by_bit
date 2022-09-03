cmake_minimum_required(VERSION 3.3)
project(bbb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ftemplate-backtrace-limit=0 -pthread")

set(SOURCE_FILES tests/main.cpp)

include_directories(./include)
add_executable(tests ${SOURCE_FILES})