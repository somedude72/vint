---
layout: default
title: Integer
nav_order: 4
permalink: /api_reference/integer
parent: API Reference
---
<a id="top"></a>

## Overview

This file contains an overview and documentation for the `vint::Int` class. It is provided by the `variable_int.hpp` header file.

## Details

The `vint::Int` class is an arbitrary precision integer type, capable of storing and manipulating numbers larger than an unsigned 64-bit integer. Just like regular integers, they behave like them and support all arithmetic operations as well as math functions. However unlike built-in integers, they start at the 32-bit size and can dynamically grow and shrink to store and represent larger integers.

Internally, it is implemented similar to Python's int object. The integer itself is stored in base 2<sup>32</sup> in a vector of `uint32_t` , where each element in the vector represents a digit. Similar to the base-10 integer system, we can add another place value by appending an element at the end of the vector when necessary. We can then "carry" the overflow into this new element, allowing for the expansion of the integer representation.

For further reading, check out [this article](https://rushter.com/blog/python-integer-implementation/) for an overview on how Python's arbitrary integer is implemented, as the overall idea and concept is the same.

## Basic Usage

This section is under construction
