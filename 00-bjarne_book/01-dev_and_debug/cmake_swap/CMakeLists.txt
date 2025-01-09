cmake_minimum_required(VERSION 3.0)
project(cmake_swap)

include_directories(includes)

add_executable(prog main.cpp src/swap.cpp src/add.cpp)
