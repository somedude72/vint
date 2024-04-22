cmake_minimum_required(VERSION 3.14)
project(vint)

set(CMAKE_CXX_STANDARD 11)

add_library(
    vint
    src/vint_constructors.cpp
    src/vint_arithmetic.cpp
    src/vint_methods.cpp
    src/voperators.cpp
)

target_include_directories(vint PUBLIC include)
