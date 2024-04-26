// Class methods (conversion, utility) definition for vint::Int
// This file contains definition for declarations in
// ../include/variable_int.hpp

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
        // Storage base (2^32) in vector
        static const std::vector<uint8_t>
            STORAGE_BASE_V = { 4, 2, 9, 4, 9, 6, 7, 2, 9, 6 };
        std::vector<uint8_t> ret = { 0 };
        std::vector<uint8_t> power = { 1 };
        for (const auto& digit : m_storage) {
            auto vec_digits = int_to_vec(digit);
            auto addend = multiply_vectors(power, vec_digits);
            ret = add_vectors(ret, addend);
            power = multiply_vectors(power, STORAGE_BASE_V);
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
}
