cmake_minimum_required(VERSION 3.5)

project(locales)

set(CMAKE_CXX_STANDARD 20)

add_executable(01 locale_handling.cpp)
add_executable(02 locale_examples.cpp)
add_executable(03 locale_facet_example.cpp)
add_executable(04 character_utilities.cpp)
add_executable(05 messages_facet.cpp)
add_executable(06 common_interface.cpp)
