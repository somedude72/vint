#include <cstdint>
#include "variable_int.hpp"
#include "voperators.hpp"

namespace vint {

    int64_t Int::to_long_long() const {
        int64_t ret = 0;
        int64_t power = 1;
        for (const auto & digit : m_storage) {
            ret += power * (int64_t)digit;
            power *= Int::STORAGE_BASE;
        }

        return (m_sign == sign::negative) ? -ret : ret;
    }

    int32_t Int::to_int() const {
        int32_t ret = 0;
        int32_t power = 1;
        for (const auto & digit : m_storage) {
            ret += power * (int32_t)digit;
            power *= Int::STORAGE_BASE;
        }

        return (m_sign == sign::negative) ? -ret : ret;
    }

    std::string Int::to_string() const {
        static const std::vector<uint8_t>
            VSTORAGE_BASE = { 4, 2, 9, 4, 9, 6, 7, 2, 9, 5 };
        std::vector<uint8_t> ret = { 0 };
        std::vector<uint8_t> power = { 1 };
        for (const auto& digit : m_storage) {
            std::vector<uint8_t> digit_in_vec = int_to_vec(digit);
            add_vectors(ret, multiply_vectors(power, digit_in_vec));
            power = multiply_vectors(power, VSTORAGE_BASE);
        }

        std::string ret_string;
        for (const auto& digit : ret)
            ret_string += std::to_string(digit);
        return (m_sign == sign::negative) ?
            '-' + ret_string : ret_string;
    }

    const std::vector<uint32_t>& Int::raw() const {
        return m_storage;
    }

    size_t Int::digits() const {
        return m_storage.size();
    }

    size_t Int::size() const {
        return sizeof(uint32_t) * m_storage.size();
    }
}
