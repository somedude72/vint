#ifndef VARIABLE_INT_HPP
#define VARIABLE_INT_HPP

#include <vector>
#include <cstdint>
#include <cstdlib>

namespace vint {

    class Int {
    public: /* Class constructors */

        Int();

        Int(int64_t number);

    public: /* Type conversion operators */

        int32_t to_int() const;

        int64_t to_long_long() const;

        std::string to_string() const;

        size_t bytes() const;

        const std::vector<uint32_t>& raw() const;

    public: /* Comparison operators [UNIMPLEMENTED] */

        // bool operator==(const Int& other);

        // bool operator<=(const Int& other);

        // bool operator>=(const Int& other);

        // bool operator<(const Int& other);

        // bool operator>(const Int& other);

        // bool operator!=(const Int& other);

        // bool operator!();

    public: /* Arithmetic operators */

      Int operator+(const Int &other) const;

      Int &operator+=(const Int &other);

      Int operator++(int);

      Int& operator++();

      // Int operator-(const Int& other) const;

      // Int operator*(const Int& other);

      // Int operator/(const Int& other);

      // Int operator%(const Int& other);

    private:
        enum sign { negative, positive };
        bool m_sign = sign::positive;
        std::vector<uint32_t> m_storage = { };
    };

}

#endif // VARIABLE_INT_HPP
