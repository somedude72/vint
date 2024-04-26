// Internal/private header file for vector operation (each
// vector represents a positive integer).

#ifndef VOPERATORS_HPP
#define VOPERATORS_HPP

#include <vector>
#include <cstdint>

std::vector<uint8_t>
int_to_vec(const uint32_t& integer);


std::vector<uint8_t>
multiply_vectors(const std::vector<uint8_t>& num_one,
                 const std::vector<uint8_t>& num_two);


std::vector<uint8_t>
add_vectors(const std::vector<uint8_t>& num_one,
            const std::vector<uint8_t>& num_two);

#endif // VOPERATORS_HPP
