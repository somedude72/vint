cmake_minimum_required(VERSION 3.14)
project(vint)

set(CMAKE_CXX_STANDARD 11)

add_library(
    vint
    src/vint/integer/constructors.cpp
    src/vint/integer/arithmetic.cpp
    src/vint/integer/methods.cpp
    src/vint/math/math.cpp
    src/utils/vectors.cpp
)

target_include_directories(vint PUBLIC include)
target_include_directories(vint PRIVATE src)
