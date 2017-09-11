cmake_minimum_required(VERSION 3.8)
project(try)

set(CMAKE_CXX_STANDARD 11)

set(MY_VAR 100)

configure_file(
        "${PROJECT_SOURCE_DIR}/foo.cfg"
        "${PROJECT_BINARY_DIR}/foo.h"
)

#set(SOURCE_FILES main.cpp)

add_library(my_lib lib_foo.cpp)

include_directories("${PROJECT_BINARY_DIR}")

include_directories("${PROJECT_SOURCE_DIR}/my_lib")
add_subdirectory(my_lib)

add_executable(try main.cpp)
target_link_libraries(try my_lib)