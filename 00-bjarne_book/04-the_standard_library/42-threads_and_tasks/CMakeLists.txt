cmake_minimum_required(VERSION 3.10)

project(threads_and_tasks)

set(CMAKE_CXX_STANDARD 20)

add_executable(01 threads_example.cpp)
add_executable(02 see_threads.cpp)
add_executable(03 concurrency_concepts.cpp)
add_executable(04 thread_synchronization_all.cpp)
add_executable(05 task_based_concurrency_example.cpp)
