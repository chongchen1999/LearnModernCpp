# Create a shared library from the source files
add_library(
    gun_soldier_shared SHARED
    gun.cpp
    solider.cpp
)

# Specify include directories for the library
target_include_directories(gun_soldier_shared PUBLIC ${CMAKE_SOURCE_DIR}/includes)
