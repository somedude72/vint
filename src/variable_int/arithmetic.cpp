// Arithmetic operator implementation for vint::Int
// This file contains definition for declarations
// in variable_int.hpp

#include "variable_int.hpp"
#include "variable_math.hpp"
#include <cstdint>

namespace vint {

    // Adds augend by addend without considering their sign (assumes
    // that both operands are positive/absolute value). 
    Int _add_vint_abs(const Int& augend, const Int& addend) {
        // Define aliases for convenience and readability
        const auto& longer = addend.m_storage.size() > augend.m_storage.size()
            ? addend : augend;
        const auto& shorter = addend.m_storage.size() <= augend.m_storage.size()
            ? addend : augend;

        Int ret = longer;
        uint32_t carry = 0;
        for (size_t i = 0; i < shorter.m_storage.size(); i++) {
            // Add from left to right (the least significant digits first) while keeping track of carries
            if ((uint32_t) (ret.m_storage[i] + carry) < ret.m_storage[i]
                || (uint32_t) (ret.m_storage[i] + shorter.m_storage[i]) < ret.m_storage[i]
                || (uint32_t) (ret.m_storage[i] + shorter.m_storage[i] + carry) < ret.m_storage[i]) {
                // If there is a carry, simply add onto the ret (taking advantage of integer overflow)
                ret.m_storage[i] += (shorter.m_storage[i] + carry);
                carry = 1;
            } else {
                // If there is not a carry, add and set carry to 0
                ret.m_storage[i] += (shorter.m_storage[i] + carry);
                carry = 0;
            }
        }

        if (carry == 0)
            return ret;

        // If there are any more carries, add 1 to the index at shorter.m_storage.size()
        for (size_t i = shorter.m_storage.size(); i <= ret.m_storage.size(); i++) {
            if (i == ret.m_storage.size()) {
                ret.m_storage.push_back(1);
                break;
            } else if (ret.m_storage[i] == UINT32_MAX) {
                ret.m_storage[i] = 0;
                continue;
            } else {
                ret.m_storage[i]++;
                break;
            }
        }

        return ret;
    }

    // Subtract minuend by subtrahend without considering their sign (assumes
    // that both operands are positive/absolute value). 
    Int _sub_vint_abs(const Int& minuend, const Int& subtrahend) {
        // Define aliases for convenience and readability
        const auto& longer = subtrahend.m_storage.size() > minuend.m_storage.size()
            ? subtrahend : minuend;
        const auto& shorter = subtrahend.m_storage.size() <= minuend.m_storage.size()
            ? subtrahend : minuend;

        Int ret = longer;
        uint32_t borrow = 0;
        for (size_t i = 0; i < shorter.m_storage.size(); i++) {
            // Add from left to right (the least significant digits first) while keeping track of carries
            if ((uint32_t) (ret.m_storage[i] - borrow) > ret.m_storage[i]
                || (uint32_t) (ret.m_storage[i] - shorter.m_storage[i]) > ret.m_storage[i]
                || (uint32_t) (ret.m_storage[i] - shorter.m_storage[i] - borrow) > ret.m_storage[i]) {
                // If there is a carry, simply add onto the ret (taking advantage of integer overflow)
                ret.m_storage[i] -= (shorter.m_storage[i] + borrow);
                borrow = 1;
            } else {
                // If there is not a carry, add and set carry to 0
                ret.m_storage[i] -= (shorter.m_storage[i] + borrow);
                borrow = 0;
            }
        }

        if (borrow == 0)
            return ret;

        for (size_t i = shorter.m_storage.size(); i <= ret.m_storage.size(); i++) {
            if (ret.m_storage[i] == 0) {
                ret.m_storage[i] = UINT32_MAX;
                continue;
            } else {
                ret.m_storage[i]--;
                break;
            }
        }
        
        return ret;
    }

    Int Int::operator+(const Int& rhs) const {
        const auto& lhs = *this;
        // Catching anything that doesn't have the possibility of going
        // "over" zero (e.g. -9 + (-100), 4 + 3, etc.)
        if (rhs.m_sign == sign::negative) {
            // Subtraction, use subtraction operator instead
            Int result = lhs - vint::abs(rhs);
            return result;
        } 

        if (lhs.m_sign == sign::positive) {
            Int result = _add_vint_abs(lhs, rhs);
            result.m_sign = sign::positive;
            return result;
        }

        // lhs.m_sign (negative) + rhs (positive). Possibility of
        // crossing over zero (e.g. -4 + 5, -10 + 11, etc.)
        Int lhs_abs = vint::abs(lhs);
        Int rhs_abs = vint::abs(rhs);
        if (lhs_abs > rhs_abs) {
            Int result = _sub_vint_abs(lhs, rhs);
            result.m_sign = sign::negative;
            return result;
        } else if (lhs_abs < rhs_abs) {
            Int result = _sub_vint_abs(rhs, lhs);
            result.m_sign = sign::positive;
            return result;
        } else {
            // When lhs == rhs
            return 0;
        }
    }

    Int& Int::operator+=(const Int& rhs) {
        Int& lhs = *this;
        if (&lhs == &rhs) {
            lhs = rhs + rhs;
            return lhs;
        } else {
            lhs = lhs + rhs;
            return lhs;
        }
    }

    Int Int::operator++(int) {
        Int temp = *this;
        *this = *this + 1;
        return temp;
    }

    Int& Int::operator++() {
        *this = *this + 1;
        return *this;
    }

    Int Int::operator-(const Int& rhs) const {
        const auto& lhs = *this;
        // Catching anything that doesn't have the possibility of going
        // "over" zero (e.g. 4 - (-3), -9 - 100, etc.)
        if (rhs.m_sign == sign::negative) {
            // Addition, use addition operator instead
            Int result = lhs + vint::abs(rhs);
            return result;
        }

        if (lhs.m_sign == sign::negative) {
            Int result = _add_vint_abs(lhs, rhs);
            result.m_sign = sign::negative;
            return result;
        }

        // lhs.m_sign (positive) - rhs (positive). Possibility of 
        // crossing over zero (e.g. 4 - 5, 9 - 11, etc.)
        Int lhs_abs = vint::abs(lhs);
        Int rhs_abs = vint::abs(rhs);
        if (lhs_abs > rhs_abs) {
            Int result = _sub_vint_abs(lhs, rhs);
            result.m_sign = sign::positive;
            return result;
        } else if (lhs_abs < rhs_abs) {
            Int result = _sub_vint_abs(rhs, lhs);
            result.m_sign = sign::negative;
            return result;
        } else {
            // When lhs == rhs
            return 0;
        }
    }

    Int& Int::operator-=(const Int& rhs) {
        Int& lhs = *this;
        if (&lhs == &rhs) {
            lhs = rhs - rhs;
            return lhs;
        } else {
            lhs = lhs - rhs;
            return lhs;
        }
    }

    Int Int::operator--(int) {
        Int temp = *this;
        *this = *this - 1;
        return temp;
    }

    Int& Int::operator--() {
        *this = *this - 1;
        return *this;
    }
}
