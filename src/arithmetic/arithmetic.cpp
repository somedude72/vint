#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "vint/integer.hpp"
#include "vint/math.hpp"

namespace vint {
    /**
     * Adds a storage vector (vector of digits in base 2^32) with another
     * storage vector. This function assumes that all preprocessing has been
     * done, and therefore ignores the sign of the integers (assumes positive)
     *
     * The function's time complexity is linear
     */
    static std::vector<uint32_t> add_storage_vector(const std::vector<uint32_t>& augend,
                                                    const std::vector<uint32_t>& addend) {
        uint32_t carry = 0;
        const auto& longer = addend.size() > augend.size() ? addend : augend;
        const auto& shorter = addend.size() <= augend.size() ? addend : augend;

        std::vector<uint32_t> result = longer;
        for (size_t i = 0; i < shorter.size(); i++) {
            const auto& value_one = result[i] + shorter[i];
            const auto& value_two = result[i] + shorter[i] + carry;
            const auto& next_digit = std::min(value_one, value_two);
            // Taking advantage of integer overflow in c++ (i.e. when adding
            // beyond the uint32_t maximum, overflows from zero again).
            if (next_digit < result[i]) {
                result[i] += shorter[i] + carry;
                carry = 1;
            } else {
                result[i] += shorter[i] + carry;
                carry = 0;
            }
        }

        if (!carry)
            return result;

        for (size_t i = shorter.size(); i <= result.size(); i++) {
            if (i == result.size()) {
                result.push_back(1);
                break;
            } else if (result[i] == UINT32_MAX) {
                result[i] = 0;
                continue;
            } else {
                result[i]++;
                break;
            }
        }

        return result;
    }

    /**
     * Subtracts a storage vector (vector of digits in base 2^32) by another
     * storage vector. This function, similar to the addition, assumes that all
     * preprocessing has been done, and therefore ignores the sign of the
     * integers
     *
     * The function's time complexity is linear
     */
    static std::vector<uint32_t> sub_storage_vector(const std::vector<uint32_t>& minuend,
                                                    const std::vector<uint32_t>& subtrahend) {
        uint32_t borrow = 0;
        const auto& longer = subtrahend.size() > minuend.size() ? subtrahend : minuend;
        const auto& shorter = subtrahend.size() <= minuend.size() ? subtrahend : minuend;

        std::vector<uint32_t> result = longer;
        for (size_t i = 0; i < shorter.size(); i++) {
            const auto& value_one = result[i] - shorter[i];
            const auto& value_two = result[i] - shorter[i] - borrow;
            const auto& next_digit = std::max(value_one, value_two);
            // Taking advantage of integer overflow (when subtracting beyond
            // zero, overflow from uint32_t maximum again).
            if (next_digit > result[i]) {
                result[i] -= shorter[i] + borrow;
                borrow = 1;
            } else {
                result[i] -= shorter[i] + borrow;
                borrow = 0;
            }
        }

        if (!borrow)
            return result;

        for (size_t i = shorter.size(); i <= result.size(); i++) {
            if (result[i] == 0) {
                result[i] = UINT32_MAX;
            } else {
                result[i]--;
                break;
            }
        }

        return result;
    }

    /**
     * Regular standard long multiplication to multiply two vectors of
     * numbers (array of digits in base 2^32). Multiplies the raw arrays
     * and ignores the signs of the digit.
     *
     * The time complexity of this function is quadratic (slow).
     */
    static std::vector<uint32_t> norm_mul_storage_vector(const std::vector<uint32_t>& multiplier,
                                                         const std::vector<uint32_t>& multiplicand) {
        std::vector<uint32_t> result = { 0 };
        result.reserve(multiplier.size() + multiplicand.size());
        constexpr uint64_t base = static_cast<uint64_t>(UINT32_MAX) + 1;
        for (size_t i = 0; i < multiplier.size(); i++) {
            uint64_t carry = 0;
            if (multiplier[i] == 0)
                continue;
            while (result.size() < i + multiplicand.size())
                result.push_back(0);
            for (size_t j = 0; j < multiplicand.size(); j++) {
                uint64_t current = (uint64_t) multiplier[i] * (uint64_t) multiplicand[j];
                uint64_t new_carry = current / base;
                current %= base;

                current += carry;
                new_carry += current / base;
                current %= base;

                current += result[i + j];
                new_carry += current / base;
                current %= base;

                carry = new_carry;
                result[i + j] = current;
            }

            while (carry) {
                result.push_back(carry % base);
                carry /= base;
            }
        }

        return result;
    }

    /**
     * Uses a non recursive toom-3 multiplication implementation to multiply
     * two array of digits. This algorithm is slower than the regular standard
     * multiplication at lower digit counts, but has a lower time complexity
     * (i.e. it gets faster as it scales).
     * 
     * The time complexity of this function is O(n^1.465), whic is better than quadratic.
     */
    static std::vector<uint32_t> fast_mul_storage_vector(const std::vector<uint32_t>& multiplier,
                                                         const std::vector<uint32_t>& multiplicand) {
        
    }

    /**
     * Processes two parameters of the Int type, and calls the correct function
     * to add or subtract the appropriate amount. The function also handles and
     * assigns the correct sign to the integers. This function is a friend of
     * the Int class, and operates directly on it.
     *
     * The time complexity of this function is O(n), where n is the number of
     * digits of the result in base 2^32.
     */
    Integer Integer::operator+(const Integer& rhs) const {
        const auto& lhs = *this;
        // Adding a negative integer is subtracting the absolute value. Please
        // note that this will be the only sineage situation that we delegate
        // to the subtraction operator. This is to prevent accidental infinite
        // recursion between addition and subtraction operators.
        if (rhs.m_sign == sign::negative) {
            Integer result = lhs - vint::abs(rhs);
            return result;
        }

        if (lhs.m_sign == sign::positive) {
            Integer result;
            result.m_sign = sign::positive;
            result.m_storage = add_storage_vector(lhs.m_storage, rhs.m_storage);
            return result;
        }

        const Integer lhs_abs = vint::abs(lhs);
        const Integer rhs_abs = vint::abs(rhs);
        if (lhs_abs > rhs_abs) {
            Integer result;
            result.m_sign = sign::negative;
            result.m_storage = sub_storage_vector(lhs.m_storage, rhs.m_storage);
            return result;
        }

        if (lhs_abs < rhs_abs) {
            Integer result;
            result.m_sign = sign::positive;
            result.m_storage = sub_storage_vector(rhs.m_storage, lhs.m_storage);
            return result;
        }

        // Opposite numbers
        return 0;
    }

    /**
     * Similar to addition, except handles subtraction instead of addition.
     * Major logic and function is similar, with some conditions are flipped
     * for subtraction. This function is a friend of the Integer class, and
     * operates directly on it.
     *
     * The time complexity of this function is O(n), where n is the number of
     * digits of the result in base 2^32.
     */
    Integer Integer::operator-(const Integer& rhs) const {
        const auto& lhs = *this;
        // Subtracting a negative integer is adding the absolute value. Please
        // note that this will be the only sineage situation that we delegate
        // to the addition operator. This is to prevent accidental infinite
        // recursion between addition and subtraction operators.
        if (rhs.m_sign == sign::negative) {
            Integer result = lhs + vint::abs(rhs);
            return result;
        }

        if (lhs.m_sign == sign::negative) {
            Integer result;
            result.m_sign = sign::negative;
            result.m_storage = add_storage_vector(lhs.m_storage, rhs.m_storage);
            return result;
        }

        const Integer lhs_abs = vint::abs(lhs);
        const Integer rhs_abs = vint::abs(rhs);
        if (lhs_abs > rhs_abs) {
            Integer result;
            result.m_sign = Integer::sign::positive;
            result.m_storage = sub_storage_vector(lhs.m_storage, rhs.m_storage);
            return result;
        } 
        
        if (lhs_abs < rhs_abs) {
            Integer result;
            result.m_sign = Integer::sign::negative;
            result.m_storage = sub_storage_vector(rhs.m_storage, lhs.m_storage);
            return result;
        }

        // Opposite numbers
        return 0;
    }

    Integer Integer::operator*(const Integer& rhs) const {
        const auto& lhs = *this;
        Integer result;
        result.m_storage = norm_mul_storage_vector(lhs.m_storage, rhs.m_storage);
        return result;
    }
}
