// Internal/private header file for vector operation (each
// vector represents a positive integer).

#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <vector>
#include <cstdint>

uint64_t vec_to_int(const std::vector<uint8_t>& vector);

std::vector<uint8_t> int_to_vec(const uint32_t& integer);

// Multiplies the array num1 by a multiplier, returning the product in another array
std::vector<uint8_t> multiply_vectors(const std::vector<uint8_t>& num1, uint64_t multiplier);

// Divide num by divisor, storing the quotient in num and returns the remainder
uint32_t divide_vectors(std::vector<uint8_t>& num, uint64_t divisor);

// Adds the two arrays num_one and num_two, returning the sum in another array
std::vector<uint8_t> add_vectors(const std::vector<uint8_t>& num_one,
                                 const std::vector<uint8_t>& num_two);

#endif // VECTORS_HPP
