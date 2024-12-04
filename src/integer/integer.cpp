#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "bases.hpp"
#include "vint/integer.hpp"

namespace vint {
    /**
     * Default constructor: constructs an instance with the number
     * initialized to zero.
     */
    Integer::Integer() = default;

    /**
     * Constructs a new instance of Int class with the number specified
     * by the number parameter.
     *
     * The time complexity of this function is linear.
     */
    Integer::Integer(const int64_t& number) {
        if (number < 0)
            m_sign = sign::negative;
        if (number == 0)
            m_storage.push_back(0);
        int_to_storage(number, m_storage);
    }

    /**
     * Constructs a new instance of Int class with the number specified
     * by the std::string. Will cause undefined behavior if the string
     * does not represent a valid integer.
     *
     * The time complexity of this function is quadratic.
     */
    Integer::Integer(const std::string& number) {
        if (number.empty())
            m_storage = { 0 };
        if (number == "-0")
            m_storage = { 0 };
        if (number[0] == '-')
            m_sign = sign::negative;
        str_to_storage(number, m_storage);
    }

    /**
     * Converts the number into its built in boolean representation.
     *
     * This will output false if the integer represented is equal to zero,
     * and true otherwise.
     */
    bool Integer::to_bool() const { return !(*this == 0); }

    /**
     * Converts the number into its long long representation. If the number
     * is greater than INT64_MAX, the resulting output will overflow.
     */
    int64_t Integer::to_long_long() const {
        int64_t temp;
        storage_to_int(m_storage, temp, m_sign);
        return temp;
    }

    /**
     * Converts the number into its int representation. If the number
     * is greater than INT32_MAX, the resulting output will overflow.
     */
    int32_t Integer::to_int() const {
        int64_t temp;
        storage_to_int(m_storage, temp, m_sign);
        return static_cast<int32_t>(temp);
    }

    /**
     * Converts the number into its std::string representation. This
     * method will never overflow, however it is significantly more
     * expensive to run.
     *
     * The time complexity of this method is quadratic.
     */
    std::string Integer::to_string() const {
        std::string temp;
        storage_to_str(m_storage, temp, m_sign);
        return temp;
    }

    /**
     * Returns the amount of memory (in bytes) that the current instance
     * of Integer is taking up.
     */
    size_t Integer::bytes() const { return sizeof(uint32_t) * m_storage.size(); }

    /**
     * Returns the internal representation (in a vector of uint32_t) of the
     * number as a const reference. The number is stored in base 2^32 as a
     * dynamic array of digits.
     */
    const std::vector<uint32_t>& Integer::raw() const { return m_storage; }

    /**
     * Less than operator for Integer
     */
    bool Integer::operator<(const Integer& comp) const {
        if (m_sign == sign::negative && comp.m_sign == sign::positive)
            return true;
        if (m_sign == sign::positive && comp.m_sign == sign::negative)
            return false;
        if (m_storage.size() < comp.m_storage.size())
            return true;
        if (m_storage.size() > comp.m_storage.size())
            return false;
        for (int64_t i = m_storage.size() - 1; i >= 0; i--) {
            if (m_sign == sign::positive && m_storage[i] < comp.m_storage[i])
                return true;
            if (m_sign == sign::negative && m_storage[i] < comp.m_storage[i])
                return false;
            if (m_sign == sign::negative && m_storage[i] > comp.m_storage[i])
                return true;
            if (m_sign == sign::positive && m_storage[i] > comp.m_storage[i])
                return false;
        }

        return false;
    }

    /**
     * Greater than operator for Integer
     */
    bool Integer::operator>(const Integer& comp) const { return !(*this < comp); }

    /**
     * Less than or equal to operator for Integer
     */
    bool Integer::operator<=(const Integer& comp) const { return !(*this > comp); }

    /**
     * Greater than or equal to operator for Integer
     */
    bool Integer::operator>=(const Integer& comp) const { return !(*this < comp); }

    /**
     * Returns the negative (opposite number) of the Integer
     */
    Integer Integer::operator-() const { return Integer(0) - *this; }

    /**
     * Checks if two Integer instances are equal to each other numerically.
     */
    bool Integer::operator==(const Integer& comp) const {
        const auto& lhs = *this;
        return (lhs.m_sign == comp.m_sign && lhs.m_storage == comp.m_storage) || 
               (lhs.m_storage == std::vector<uint32_t> { 0 } && comp.m_storage == std::vector<uint32_t> { 0 });
    }
}
