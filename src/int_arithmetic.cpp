// Arithmetic operator implementation for vint::Int
// This file contains definition for declarations
// in ../include/variable_int.hpp

#include "variable_int.hpp"
#include <cstdint>

namespace vint {

    Int Int::operator+(const Int& rhs) const {
        const auto& lhs = *this;
        const auto& longer = rhs.m_storage.size() > lhs.m_storage.size()
            ? rhs : lhs;
        const auto& shorter = rhs.m_storage.size() <= lhs.m_storage.size()
            ? rhs : lhs;

        Int ret = longer;
        uint32_t carry = 0;
        for (size_t i = 0; i < shorter.m_storage.size(); i++) {
            if ((uint32_t) (ret.m_storage[i] + carry) < ret.m_storage[i]
                || (uint32_t) (ret.m_storage[i] + shorter.m_storage[i]) < ret.m_storage[i]
                || (uint32_t) (ret.m_storage[i] + shorter.m_storage[i] + carry) < ret.m_storage[i]) {
                ret.m_storage[i] += (shorter.m_storage[i] + carry);
                carry = 1;
            } else {
                ret.m_storage[i] += (shorter.m_storage[i] + carry);
                carry = 0;
            }
        }

        if (carry == 0)
            return ret;

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
        *this += 1;
        return temp;
    }


    Int& Int::operator++() {
        *this += 1;
        return *this;
    }

}
