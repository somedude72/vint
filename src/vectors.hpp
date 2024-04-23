// Internal/private header file for vector operation (each
// vector represents a positive integer).

#ifndef VOPERATORS_HPP
#define VOPERATORS_HPP

#include <vector>
#include <cstdint>

std::vector<uint8_t> int_to_vec(uint32_t integer);

void perform_addition(std::vector<uint8_t>& num_two,
                      std::vector<uint8_t>& num_one);

void process_overflow(std::vector<uint8_t>& vector,
                      const int32_t base = 10);

void align_vectors(std::vector<uint8_t>& v1,
                   std::vector<uint8_t>& v2);

void align_vectors(std::vector<uint32_t>& v1,
                   std::vector<uint32_t>& v2);

void add_vectors(std::vector<uint8_t>& num_one,
                 std::vector<uint8_t>&& num_two);

std::vector<uint8_t> multiply_vectors(const std::vector<uint8_t>& num_one,
                                      const std::vector<uint8_t>& num_two);

#endif // VOPERATORS_HPP
