cmake_minimum_required(VERSION 3.14)
project(vint)

set(CMAKE_CXX_STANDARD 11)

add_library(
    vint
    src/integer/bases.cpp
    src/integer/integer.cpp
    src/arithmetic/arithmetic.cpp
    src/math/math.cpp
)

target_include_directories(vint PUBLIC include)
target_include_directories(vint PRIVATE src/integer)
