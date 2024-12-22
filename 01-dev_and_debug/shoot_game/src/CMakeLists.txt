# Create a static library from the source files
add_library(
    gun_soldier_lib
    gun.cpp
    solider.cpp
)

# Specify include directories for the library
target_include_directories(gun_soldier_lib PUBLIC ${CMAKE_SOURCE_DIR}/includes)
