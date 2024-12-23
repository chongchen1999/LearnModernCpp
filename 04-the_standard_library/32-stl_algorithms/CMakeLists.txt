cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MatrixProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the executable and source files
add_executable(01 stl_algorithms_demo.cpp)
add_executable(02 nonmodifying_and_modifying_algorithms.cpp)
add_executable(03 min_max_algorithms.cpp)
