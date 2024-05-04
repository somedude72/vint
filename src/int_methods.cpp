// Class methods (conversion, utility) implementation for vint::Int
// This file contains definition for declarations
// in variable_int.hpp

#include <cstdint>

#include "variable_int.hpp"
#include "vectors.hpp"

namespace vint {

    int64_t Int::to_long_long() const {
        int64_t ret = 0;
        int64_t power = 1;
        for (const auto & digit : m_storage) {
            ret += power * (int64_t) digit;
            power *= UINT32_MAX;
        }

        return (m_sign == sign::negative) ? -ret : ret;
    }

    int32_t Int::to_int() const {
        int32_t ret = 0;
        int32_t power = 1;
        for (const auto & digit : m_storage) {
            ret += power * (int32_t) digit;
            power *= UINT32_MAX;
        }

        return (m_sign == sign::negative) ? -ret : ret;
    }

    std::string
    Int::to_string() const {
        std::vector<uint8_t> ret = { 0 };
        std::vector<uint8_t> power = { 1 };
        for (const auto& digit : m_storage) {
            auto addend = multiply_vectors(power, digit);
            ret = add_vectors(ret, addend);
            power = multiply_vectors(power, (uint64_t) UINT32_MAX + 1);
        }

        std::string ret_string;
        for (const auto& digit : ret)
            ret_string += std::to_string(digit);
        return (m_sign == sign::negative)
            ? '-' + ret_string : ret_string;
    }

    const std::vector<uint32_t>&
    Int::raw() const {
        return m_storage;
    }

    size_t Int::bytes() const {
        return sizeof(uint32_t) * m_storage.size();
    }

    bool Int::operator==(const Int& rhs) const {
        return m_sign == rhs.m_sign &&
               m_storage == rhs.m_storage;
    }

    bool Int::operator!=(const Int& rhs) const {
        return !(rhs == *this);
    }

    bool Int::operator<(const Int& rhs) const {
        if (m_sign == sign::negative && rhs.m_sign == sign::positive)
            return true;
        if (m_sign == sign::positive && rhs.m_sign == sign::negative)
            return false;
        if (m_storage.size() < rhs.m_storage.size())
            return true;
        if (m_storage.size() > rhs.m_storage.size())
            return false;
        for (int64_t i = m_storage.size() - 1; i >= 0; i--) {
            if (m_sign == sign::positive && m_storage[i] < rhs.m_storage[i])
                return true;
            if (m_sign == sign::positive && m_storage[i] > rhs.m_storage[i])
                return false;
            if (m_sign == sign::negative && m_storage[i] > rhs.m_storage[i])
                return true;
            if (m_sign == sign::negative && m_storage[i] < rhs.m_storage[i])
                return false;
        }

        return false;
    }

    bool Int::operator>(const Int& rhs) const {
        return !(*this < rhs);
    }

    bool Int::operator<=(const Int& rhs) const {
        return !(*this > rhs);
    }

    bool Int::operator>=(const Int& rhs) const {
        return !(*this < rhs);
    }

    bool Int::operator!() const {
        return *this == 0;
    }
}
