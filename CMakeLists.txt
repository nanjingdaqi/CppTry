cmake_minimum_required(VERSION 3.8)
project(try)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(try ${SOURCE_FILES})