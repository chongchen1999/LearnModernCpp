cmake_minimum_required(VERSION 3.10)

# Project name
project(SoldierGunProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Add the src directory
add_subdirectory(src)

# Add the main executable
add_executable(main main.cpp)

# Link the shared library from src to the main executable
target_link_libraries(main PRIVATE gun_soldier_shared)
