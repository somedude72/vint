#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>

#include "bases.hpp"

namespace vint {
    /**
     * Helper function for adding the two arrays augend and addend. Returns the sum in
     * another array.
     *
     * This function performs addition in linear time and assumes that both numbers and
     * the output is in base 10
     */
    static std::vector<uint8_t> add_arrays(const std::vector<uint8_t>& augend,
                                           const std::vector<uint8_t>& addend) {
        std::vector<uint8_t> result;
        const size_t size = std::max(augend.size(), addend.size());
        uint8_t carry = 0;

        result.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            constexpr int BASE = 10;
            uint8_t digit1 = (i < augend.size()) ? augend[augend.size() - 1 - i] : 0;
            uint8_t digit2 = (i < addend.size()) ? addend[addend.size() - 1 - i] : 0;
            uint8_t sum = digit1 + digit2 + carry;
            result.push_back(sum % BASE);
            carry = sum / BASE;
        }

        if (carry > 0)
            result.push_back(carry);
        std::reverse(result.begin(), result.end());
        return result;
    }

    /**
     * Helper function that multiplies the array multiplier by a multiplicand, returning
     * the product in another array.
     *
     * This function performs multiplication in linear time.
     */
    static std::vector<uint8_t> multiply_arrays(const std::vector<uint8_t>& multiplier,
                                                uint64_t multiplicand) {
        std::vector<uint64_t> temp(multiplier.begin(), multiplier.end());
        uint64_t prev_carry = 0;
        uint64_t curr_carry = 0;
        for (int64_t i = temp.size() - 1; i >= 0; i--) {
            temp[i] *= multiplicand;

            curr_carry = temp[i] / 10;
            temp[i] %= 10;
            temp[i] += prev_carry;

            curr_carry += (temp[i] / 10);
            temp[i] %= 10;
            prev_carry = curr_carry;
        }

        while (prev_carry) {
            temp.insert(temp.begin(), prev_carry % 10);
            prev_carry /= 10;
        }

        while (!temp.empty() && temp.front() == 0)
            temp.erase(temp.begin());
        return temp.empty()
                   ? std::vector<uint8_t> { 0 }
                   : std::vector<uint8_t>(temp.begin(), temp.end());
    }

    /**
     * Helper function to divide dividend by divisor, storing the quotient in dividend and
     * returns the remainder.
     *
     * The time complexity of this function is linear.
     */
    static uint64_t divide_arrays(std::vector<uint8_t>& dividend, uint64_t divisor) {
        uint64_t remainder = 0;
        for (auto& digit : dividend) {
            uint64_t dividend_part = remainder * 10 + digit;
            digit = dividend_part / divisor;
            remainder = dividend_part % divisor;
        }

        while (!dividend.empty() && dividend.front() == 0)
            dividend.erase(dividend.begin());
        return remainder;
    }

    /**
     * The most primitive way to convert a c++ long long (base 10) into
     * a vector of digits in base 2^32 to store in the Int class.
     *
     * The time complexity of this function is linear.
     */
    void ll_to_storage(int64_t number, std::vector<uint32_t>& storage) {
        number = std::abs(number);
        constexpr int64_t storage_base = static_cast<int64_t>(UINT32_MAX) + 1;

        while (number) {
            storage.push_back(number % storage_base);
            number /= storage_base;
        }
    }

    /**
     * The most primitive way to convert a c++ std::string (base 10) into
     * a vector of digits in base 2^32 to store in the Int class.
     *
     * The time complexity of this function is quadratic.
     */
    void str_to_storage(std::string number, std::vector<uint32_t>& storage) {
        const size_t num_start = number[0] == '-' ? 1 : 0;
        std::vector<uint8_t> num_vec(number.size() - num_start);
        for (size_t i = num_start; i < number.size(); i++)
            num_vec[i - num_start] = number[i] - '0';

        constexpr uint64_t base =
            static_cast<uint64_t>(UINT32_MAX) + 1;
        while (!number.empty()) {
            storage.push_back(divide_arrays(num_vec, base));
        }
    }

    /**
     * Converts a vector of digits in base 2^32 (storage base) into a base 10
     * integer (operates in place, i.e. number is passed by reference).
     *
     * The time complexity of this function is linear.
     */
    int64_t storage_to_ll(const std::vector<uint32_t>& storage, bool negative) {
        int64_t ret = 0;
        int64_t power = 1;
        for (const auto& digit : storage) {
            ret += power * static_cast<int64_t>(digit);
            power *= UINT32_MAX;
        }

        return (negative) ? -ret : ret;
    }

    /**
     * Converts a vector of digits in base 2^32 (storage base) into a base 10
     * string (operates in place, i.e. std::string is passed by reference).
     *
     * The time complexity of this function is quadratic.
     */
    std::string storage_to_str(const std::vector<uint32_t>& storage, bool negative) {
        std::vector<uint8_t> ret = { 0 };
        std::vector<uint8_t> power = { 1 };
        std::string result = "";
        for (const auto& digit : storage) {
            constexpr uint64_t base = static_cast<uint64_t>(UINT32_MAX) + 1;
            ret = add_arrays(ret, multiply_arrays(power, digit));
            power = multiply_arrays(power, base);
        }

        for (const auto& digit : ret)
            result += std::to_string(digit);
        if (negative)
            result.insert(result.begin(), '-');
        return result;
    }
}
