---
layout: default
title: Home
permalink: /home
nav_order: 1
---
<a id="top"></a>

## Home

Vint is a header only arbitrary precision integer library in c++. See the [repository](https://github.com/somedude72/vint/blob/main). 

This website will contain quickstart tutorials, documentation, and other info for the project. Use the sidebar on the left hand side to find and navigate between pages and documentation. Please note that this is a hobby project of mine, which means maintenance will not be guaranteed for the long run. 

## Quickstart

Because this is a header only library, installation is very straightforward. Simply clone the repository and move the of the include directory into where you need it. 

```sh
$ git clone https://github.com/somedude72/vint
$ mv vint/include path/to/project/include
```
Now you are ready to use the library. See the example below or read the [tutorial](/tutorial)

```cpp
#include <iostream>
#include "vint/integer.hpp"

int main() {
    // initializes a variable int object
    vint::Integer a = 1;
    for (int i = 0; i < 1024; i++)
        // double a 1024 times (equivalent of 2^1024)
        a += a;
    // prints 'a' by converting it to int64_t
    std::cout << "int64_t val: " << a.to_long_long() << '\n';
    // prints 'a' by converting it to std::string (overflow-proof)
    std::cout << "std::string val: " << a.to_string() << '\n';
}
```

## About

This documentation is created with the [Just The Docs](https://github.com/just-the-docs/just-the-docs) Jekyll theme and hosted on [GitHub Pages](https://pages.github.com/). All credits go to their respective authors.
