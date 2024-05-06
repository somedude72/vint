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
    auto beg_nonzero = std::find_if_not(temp.begin(), temp.end(),
        [](uint64_t digit) { return digit == 0; });
    std::vector<uint8_t> ret(beg_nonzero, temp.end());
    return ret.empty()
        ? std::vector<uint8_t>{ 0 } : ret;
}

uint32_t divide_vectors(std::vector<uint8_t>& num, uint64_t divisor) {
    std::vector<uint8_t> quotient(num.size());
    // Num.size should remain constant for the loop to work
    for (size_t i = 0; i < num.size(); i++) {
        // Load the dividend into an integer to work with easier
        uint64_t dividend = vec_to_int(std::vector<uint8_t>(num.begin(), num.begin() + i + 1));

        quotient[i] = dividend / divisor;
        uint64_t subtract = quotient[i] * divisor;
        uint64_t new_dividend = dividend - subtract;

        // Insert zero in front to retain num.size
        std::vector<uint8_t> dividend_vec = int_to_vec(new_dividend);
        for (size_t j = 0; j <= i; j++) {
            if (j < i - dividend_vec.size() + 1) {
                num[j] = 0;
            } else {
                num[j] = dividend_vec[j - (i - dividend_vec.size() + 1)];
            }
        }
    }

    auto beg_quotient_nonzero = std::find_if_not(
        quotient.begin(), quotient.end(), 
        [](uint8_t& digit) { return digit == 0; }
    );

    auto beg_mod_nonzero = std::find_if_not(
        num.begin(), num.end(), 
        [](uint8_t& digit) { return digit == 0; }
    );

    std::string temp_mod;
    for (auto it = beg_mod_nonzero; it != num.end(); it++)
        temp_mod += (char) ((uint32_t) *it + '0');
    if (temp_mod.empty())
        temp_mod = '0';
    uint32_t mod = std::stoll(temp_mod);

    num = std::vector<uint8_t>(beg_quotient_nonzero, quotient.end());
    return mod;
}