// Implementation file for vectors.hpp

#include <algorithm>
#include <cstdint>
#include <vector>

#include "vectors.hpp"

std::vector<uint8_t>
int_to_vec(const uint32_t& integer) {
    // Loads integer into a string for convenience
    std::string string = std::to_string(integer);
    std::vector<uint8_t> ret = { };
    for (const auto& character : string)
        ret.push_back(character - '0');
    return ret;
}


std::vector<uint8_t>
add_vectors(const std::vector<uint8_t>& num_one,
            const std::vector<uint8_t>& num_two) {
    std::vector<uint8_t> ret;
    size_t size = std::max(num_one.size(), num_two.size());
    uint8_t carry = 0;
    const int BASE = 10;

    ret.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        // Performing addition from right to left (least significant digits first)
        uint8_t digit1 = (i < num_one.size()) ? num_one[num_one.size() - 1 - i] : 0;
        uint8_t digit2 = (i < num_two.size()) ? num_two[num_two.size() - 1 - i] : 0;
        uint8_t sum = digit1 + digit2 + carry;
        ret.push_back(sum % BASE);
        carry = sum / BASE;
    }

    if (carry > 0)
        ret.push_back(carry);
    std::reverse(ret.begin(), ret.end()); // Reverse to store most significant digits first
    return ret;
}


std::vector<uint8_t>
multiply_vectors(const std::vector<uint8_t>& num1, uint64_t multiplier) {
    std::vector<uint64_t> temp(num1.size());
    for (size_t i = 0; i < temp.size(); i++) {
        // Load num1 into a uint64_t vector for simplicity
        temp[i] = (uint64_t) num1[i];
        temp[i] *= multiplier;
    }

    uint64_t prev_carry = 0;
    uint64_t curr_carry = 0;
    for (int64_t i = temp.size() - 1; i >= 0; i--) {
        // Compute each digit while keeping track of carries
        curr_carry = temp[i] / 10;
        temp[i] %= 10;
        temp[i] += prev_carry;

        curr_carry += (temp[i] / 10);
        temp[i] %= 10;
        prev_carry = curr_carry;
    }

    while (prev_carry) {
        // If any carries are left, keep inserting them at the front
        temp.insert(temp.begin(), prev_carry % 10);
        prev_carry /= 10;
    }

    // Truncate leading zeros and return in a uint8_t vector
    auto beg_nonzero = std::find_if_not(temp.begin(), temp.end(),
        [](uint64_t digit) { return digit == 0; });
    std::vector<uint8_t> ret(beg_nonzero, temp.end());
    return ret.size() == 0
        ? std::vector<uint8_t>{ 0 } : ret;
}
