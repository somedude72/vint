---
layout: default
title: Home
permalink: /home
nav_order: 1
---
<a id="top"></a>

## Home

Vint is an arbitrary precision integer library in c++. It is also the first project and library that I've written in c++.

For an overview of some basic information of this library to get you started, check out the repository [readme](https://github.com/SomedudeX/vint/blob/main/README.md) file. This website will contain quickstart tutorials, detailed documentation, repository status, among other finer details and information. Use the sidebar on the left hand side to find and navigate between pages and documentation. This documentation page is still a work in progress, and parts of it may be incomplete or missing.

## Quickstart

The following tutorial will install and setup the vint library in a CMake project as well as demonstrate basic examples and usages of this library. Make sure you have both CMake and Make installed and on your path before continuing. At least c++11 is required to compile vint.

 * Add the library as a git submodule

```sh
git submodule add https://github.com/SomedudeX/vint.git extern/vint
git submodule update --init
cd extern/vint
```

 * Build the library with CMake

```sh
mkdir build && cd build
cmake -S ../ && make
```

 * Add the following lines to your CMakeLists.txt

```cmake
target_include_directories(ProjectName PUBLIC extern/vint/include)
target_link_directories(ProjectName PUBLIC extern/vint/build)
target_link_libraries(ProjectName vint)
```

Done! See the example usages of the library below, check out the [tutorial](/tutorial/) or browse any of the API overviews on the left sidebar for more details on the usage of this library. Alternatively, you can also read the documentation in the public header files for more information on a specific class or function.

```cpp
#include <iostream>
#include "variable_int.hpp"

int main() {
    // initializes a variable int object
    vint::Int a = 1;
    for (int i = 0; i < 1024; i++)
        // double a 1024 times (equivalent of 2^1024)
        a += a;
    // prints 'a' by converting it to int64_t
    std::cout << "int64_t val: " << a.to_long_long() << '\n';
    // prints 'a' by converting it to std::string (overflow-proof)
    std::cout << "std::string val: " << a.to_string() << '\n';
}
```

## Project Roadmap

Below is a list of features planned for this library. The checkmark next to them represents their rough status in development (a checkmark means that it is already implemented, no checkmark means that the feature is currently being worked on). This roadmap is only a rough to-do list for this repository, and may change without notice at any point in time.

 - [x] Integer addition
 - [ ] Integer subtraction
 - [ ] Integer multiplication
 - [ ] Integer division
 - [ ] Integer `std::string` constructor
 - [x] Integer conversion methods

Below is a list of features that is not currently being worked on, however may be added to the repository.

 - [ ] Floating point numbers
 - [ ] Integer modulo operator
 - [ ] Integer math functions

## About

This documentation is created with the [Just The Docs](https://github.com/just-the-docs/just-the-docs) Jekyll theme and hosted on [GitHub Pages](https://pages.github.com/). All credits go to their respective authors.
