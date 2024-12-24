cmake_minimum_required(VERSION 3.10)

project(concurrency)

set(CMAKE_CXX_STANDARD 20)

add_executable(01 concurrency_example.cpp)
add_executable(02 atomic_volatile_example.cpp)