cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MatrixProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the executable and source files
add_executable(matrix_test matrix_test.cpp)

# Include directories
target_include_directories(matrix_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
