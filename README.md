## Overview

An arbitrary precision integer and floating point library in C++. This library is implemented similar to Python's integer object.

> [!WARNING]
> This library is in pre-alpha development: API may and will change without warning. Please do not use this unless you would like to contribute to it.

## Quickstart

Make sure you have Make and CMake installed and on your path before continuing.

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

```java
target_include_directories(ProjectName PUBLIC extern/vint/include)
target_link_directories(ProjectName PUBLIC extern/vint/build)
target_link_libraries(ProjectName vint)
```

Done! See the [example](#examples) usages of the library below, or check out the [documentation](https://github.com/SomedudeX/vint/tree/main/docs) for more details on the usage of this library

## Examples

```cpp
#include <iostream>
#include "variable_int.hpp"

int main() {
    vint::Int a = 1;  // initializes a variable int object
    for (int i = 0; i < 1024; i++)
        a += a;       // double a 1024 times (equivalent of 2^1024)
    // prints 'a' by converting it to int64_t
    std::cout << "int64_t val: " << a.to_long_long() << '\n';
    // prints 'a' by converting it to std::string (overflow-proof)
    std::cout << "std::string val: " << a.to_string() << '\n';
}
```

## Notes

Currently only the addition with positive integers are implemented. The rest of the operations (e.g. subtraction, decrement, etc), comparison operators (e.g. less, greater, not, etc), as well as floating point numbers are still a work in progress.
