// Implementation file for vectors.hpp

#include <algorithm>
#include <cstdint>
#include <vector>

#include "vectors.hpp"

static uint64_t integer_power(uint64_t base, uint64_t exp) {
    uint64_t ret = 1;
    while (exp > 0) {
        uint64_t last_bit = (base & 1);
        if (last_bit)
            ret = ret * base;
        base *= base;
        exp = exp >> 1;
    }

    return ret;
}

std::vector<uint8_t> int_to_vec(uint64_t integer) {
    // Loads integer into a string for convenience
    std::string string = std::to_string(integer);
    std::vector<uint8_t> ret = { };
    for (const auto& character : string)
        ret.push_back(character - '0');
    return ret;
}

uint64_t vec_to_int(const std::vector<uint8_t>& vector) {
    uint64_t ret = 0;
    for (size_t i = 0; i < vector.size(); i++)
        ret += vector[i] * integer_power(10, vector.size() - i - 1);
    return ret;
}

std::vector<uint8_t> add_vectors(const std::vector<uint8_t>& num_one,
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

std::vector<uint8_t> multiply_vectors(const std::vector<uint8_t>& num1, uint64_t multiplier) {
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
    int64_t beg_nonzero = temp.size();
    for (size_t i = 0; i < temp.size(); i++) {
        if (temp[i] != 0) {
            beg_nonzero = i;
            break;
        }
    }

    temp.erase(temp.begin(), temp.begin() + beg_nonzero);
    return temp.empty()
        ? std::vector<uint8_t>{ 0 } : std::vector<uint8_t>(temp.begin(), temp.end());
}

uint64_t divide_vectors(std::vector<uint8_t>& dividend, uint64_t divisor) {
    uint64_t remainder = 0;

    for (size_t i = 0; i < dividend.size(); i++) {
        uint64_t dividend_part = remainder * 10 + dividend[i];
        dividend[i] = dividend_part / divisor;
        remainder = dividend_part % divisor;
    }

    int64_t beg_nonzero = dividend.size();
    for (size_t i = 0; i < dividend.size(); i++) {
        if (dividend[i] != 0) {
            beg_nonzero = i;
            break;
        }
    }

    dividend.erase(dividend.begin(), dividend.begin() + beg_nonzero);
    return remainder;
}