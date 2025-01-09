cmake_minimum_required(VERSION 3.10)

project(the_c_standard_library)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

add_executable(01 stdio_examples.c)
add_executable(02 c_standard_library_demo.c)