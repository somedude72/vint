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
multiply_vectors(const std::vector<uint8_t>& num1,
                 const std::vector<uint8_t>& num2) {
    size_t n = num1.size();
    size_t m = num2.size();
    const int BASE = 10;
    std::vector<uint8_t> ret(n + m, 0);
    for (int32_t i = n - 1; i >= 0; i--) {
        for (int32_t j = m - 1; j >= 0; j--) {
            int32_t mul = num1[i] * num2[j];
            int32_t sum = mul + ret[i + j + 1];
            ret[i + j] += sum / BASE;
            ret[i + j + 1] = sum % BASE;
        }
    }

    auto beg_nonzero = std::find_if_not(
        ret.begin(), ret.end(),
        [](uint8_t i) { return i == 0; }); // Remove leading zeros
    return beg_nonzero == ret.end()
        ? std::vector<uint8_t>{ 0 }
        : std::vector<uint8_t>(beg_nonzero, ret.end());
}
