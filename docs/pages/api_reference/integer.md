---
layout: default
title: Integer
nav_order: 4
permalink: /api_reference/integer
parent: API Reference
---
<a id="top"></a>

## Overview

This file contains an overview and documentation for symbols in the `vint/integer.hpp` header file.

The `vint::Integer` class is an arbitrary precision integer type, capable of storing and manipulating integers that exceed machine word size. The class behaves just like regular integers, supporting all arithmetic operations and math functions. Internally, it represents the integer starting at the size of the base storage type, and dynamically allocate more or less space to store larger integers.

Common methods for the construction, comparison, and arithmetic of this class are provided in this header, in addition to some basic math functions. A concise description of each symbol exposed through this header follows. 

## Integer Class

**`Integer()`**

Constructor. Initializes the object to zero by default.

**`Integer(const int64_t& num)`**

Constructor. Initializes the object from a primitive integer type. For integers over the limit for 64-bit signed representations, construct using a string instead. 

**`Integer(const std::string& num)` `(explicit)`**

Constructor. Initializes the object from a string that is a integer in base-10. If num is not a valid base-10 integer, the object will be initialized to zero. This is marked explicit to avoid accidentally doing math with strings. 

**`bool to_bool() const`** <br>
**`std::int64_t to_int64() const`** <br>
**`std::string to_string() const`**

Casting the object to other types:
 - Cast to bool in $ O(1) $. This is equivalent to checking if the object is not zero. 
 - Cast to std::int64_t in $ O(1) $. This will overflow for integers greater than INT64_MAX.
 - Cast to std::string in $ O(n^2) $. This won't overflow for large integers. 

**`bool operator<(const vint::Integer& lhs, const vint::Integer& rhs)`** <br>
**`bool operator>(const vint::Integer& lhs, const vint::Integer& rhs)`** <br>
**`bool operator<=(const vint::Integer& lhs, const vint::Integer& rhs)`** <br>
**`bool operator>=(const vint::Integer& lhs, const vint::Integer& rhs)`** <br>
**`bool operator==(const vint::Integer& lhs, const vint::Integer& rhs)`** <br>
**`bool operator!=(const vint::Integer& lhs, const vint::Integer& rhs)`**

Comparison operators in $ O(1) $.

**`vint::Integer operator+(const vint::Integer& val)`** <br>
**`vint::Integer operator-(const vint::Integer& val)`**

Urinary operators for addition and subtraction in $ O(1) $

**`vint::Integer operator+(const vint::Integer& lhs, const vint::Integer& rhs)`** <br>
**`vint::Integer operator-(const vint::Integer& lhs, const vint::Integer& rhs)`** <br>
**`vint::Integer operator*(const vint::Integer& lhs, const vint::Integer& rhs)`** <br>
**`vint::Integer operator/(const vint::Integer& lhs, const vint::Integer& rhs)`**

Binary operators for addition, subtraction, multiplication, and division. 

 - Addition is computed in $ O(n) $. 
 - Subtraction is computed in $ O(n) $.
 - Multiplication is computed in $ O(n^{1.465}) $. Large integers use Toom-3 multiplication for better asymptotic performance; small integers use schoolbook multiplication for its faster constant factor runtime. 
 - Division is computed in $ O(n^{1.465}) $. Large integers use Netwon-Raphson division for better asymptotic performance; small integers use schoolbook division for its faster constant factor runtime. 

## Math Functions

**`Integer abs(const Integer& val)`**

Absolute value function in $ O(1) $. Returns the non-negative value of the value.

**`Integer sgn(const Integer& val)`**

Sign function in $ O(1) $. Returns $ -1 $ if the value is negative, $ 1 $ if it is positive, and $ 0 $ if it is zero. 

**`Integer max(const Integer& a, const Integer& b)`**

Maximum of the two integers in $ O(1) $. Returns the greater of a and b.

**`Integer min(const Integer& a, const Integer& b)`**

Minumum of the two integers in $ O(1) $. Returns the lesser of a and b.

**`ipow(const Integer& base, const Integer& exp)`**

Fast integer power in $ O(\log n) $. Returns base to the power of exp. 

**`fact(const Integer& val)`**

Naive factorial of the value. 

## Example

The following is a basic example of the usage of this class. 

```cpp
#include <iostream>
#include "vint/integer.hpp"

int main() {
    vint::Integer n = vint::Integer("1234567890987654321");
    std::cout << vint::ipow(n, 100).to_string();
    std::cout << (-n * 123456789).to_string();
}
```