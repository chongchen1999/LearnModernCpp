cmake_minimum_required(VERSION 3.0)
project(shoot_game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -g -O2 -Wall")

include_directories(${CMAKE_SOURCE_DIR}/includes)

add_executable(shoot_game main.cpp src/gun.cpp src/solider.cpp)
