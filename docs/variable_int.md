## Class `vint::Int`

An arbitrary precision integer type in C++. Provided by `variable_int.hpp`.

## Public Methods

#### `Int ()`

* Initializes an `vint::Int` object with the represented number initialized to 0 and sign to positive.

#### `Int (int64_t number)`

* Initializes the `vint::Int` object with a number.
* Param `number` - The number that the object shall hold. This must be within signed 64-bit integer. If a bigger initial number is required, use the `std::string` constructor instead (currently unimplemented).

#### `Int (std::string number)`

* Initializes the `vint::Int` object with a string.
* Param `number` - The number (in string) to construct the instance with. This method is significantly slower than using the long long constructor, however it is integer overflow-proof, meaning that any arbitrarily large number could be used here.
* This method is currently unimplemented.

#### `operator int64_t () const`

* `int64_t` conversion operator.
* Returns the number in `int64_t`. Regular overflow rules apply.
* This operator has not been marked explicit because this class is written to behave like a regular C++ integer.

#### `std::string to_string () const`

* `std::string` convertion operator.
* Returns the number in `std::string`. Integer overflow rules does not apply.
* The time complexity of this method is O(n^3) where n is the number of digits of the number in base `2^32`
* This method is integer overflow-proof. However, in order to make it so, complicated (and expensive) vector operations had to be implemented in place of the regular integer operators when using the `int64_t` conversion operator. Because of this, this method will not scale well as the size of the integer gets larger. To address this issue (which is my laziness of not optimizing), you can write your own to_string  conversion operator. You can access the underlying storage vector by using the `raw()` method of this class. From there, have fun converting a vector representing a number stored in base 2^32 (where each element represents a digit) into a string in base 10.

#### `size_t elements () const`

* Getter for the size of the raw array.
* Returns a `size_t` representing the size of the raw array

#### `size_t size () const`

* Computes the total size (in bytes) allocated.
* Returns a `size_t` representing the total size (in bytes) taken up by the `vint::Int` object

#### `std::vector<uint32_t> & raw ()`

* Getter for the raw array.
* Returns a reference to the raw array.

#### `vint::Int operator+ (const vint::Int &other) const`

* Addition operator for `vint::Int`.
* Returns an `vint::Int` object representing the sum of `this` and `other`.
* The time complexity of this method is O(n) where n is the number of digits of the number in base `2^32`.

## Details

All basic logical and binary operators have been implemented. See individual method documentation for more details.

This class has been written to behave like a regular C++ integer. Implemented similar to Python's `int` object. The integer itself is stored in base `2^32` (or base `4,294,967,296`) in a vector of `uint32_t` , where each element in the vector represents a digit. For more information, see [this article](https://rushter.com/blog/python-integer-implementation/) for details on how Python's arbitrary integer is implemented, as the overall idea/concept is the same.
