cmake_minimum_required(VERSION 3.14)
project(vint)

set(CMAKE_CXX_STANDARD 11)

add_library(
    vint
    src/variable_int/constructors.cpp
    src/variable_int/arithmetic.cpp
    src/variable_int/methods.cpp
    src/variable_math.cpp
    src/vectors.cpp
)

target_include_directories(vint PUBLIC include)
target_include_directories(vint PRIVATE src)
