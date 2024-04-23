cmake_minimum_required(VERSION 3.14)
project(vint)

set(CMAKE_CXX_STANDARD 11)

add_library(
    vint
    src/int_constructors.cpp
    src/int_arithmetic.cpp
    src/int_methods.cpp
    src/vectors.cpp
)

target_include_directories(vint PUBLIC include)
