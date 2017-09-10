cmake_minimum_required(VERSION 3.8)
project(try)

set(CMAKE_CXX_STANDARD 11)

set(MY_VAR daqi)

configure_file(
        "${PROJECT_SOURCE_DIR}/foo.cfg"
        "${PROJECT_BINARY_DIR}/foo.h"
)

set(SOURCE_FILES main.cpp)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(try ${SOURCE_FILES})