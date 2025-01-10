cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Basics)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the executable
add_executable(hw01 hw01.cpp)
add_executable(hw02 hw02.cpp)
add_executable(hw03 hw03.cpp)
add_executable(hw04 hw04.cpp)
add_executable(hw05 hw05.cpp)
add_executable(hw06 hw06.cpp)
add_executable(hw07 hw07.cpp)
add_executable(hw08 hw08.cpp)
add_executable(hw09 hw09.cpp)
add_executable(hw10 hw10.cpp)
add_executable(hw11 hw11.cpp)
add_executable(hw12 hw12.cpp)
add_executable(hw13 hw13.cpp)
add_executable(hw14 hw14.cpp)

# Apply -ftrapv only to limits_.cpp
set_source_files_properties(hw01.cpp PROPERTIES COMPILE_FLAGS -ftrapv)