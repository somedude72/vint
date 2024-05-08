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

        explicit Int(const std::string& number);

    public: /* Type conversion operators */

        int32_t to_int() const;

        int64_t to_long_long() const;

        std::string to_string() const;

        bool to_bool() const;

        size_t bytes() const;

        const std::vector<uint32_t>& raw() const;

    public: /* Arithmetic operators */

        Int operator+(const Int& rhs) const;

        Int& operator+=(const Int& rhs);

        Int operator++(int);

        Int& operator++();

        Int operator-(const Int& rhs) const;

        Int& operator-=(const Int& rhs);

        Int operator--(int);

        Int& operator--();

    public: /* Relational operators */

        bool operator==(const Int& rhs) const;

        bool operator!=(const Int& rhs) const;

        bool operator<(const Int& rhs) const;

        bool operator>(const Int& rhs) const;

        bool operator<=(const Int& rhs) const;

        bool operator>=(const Int& rhs) const;

        bool operator!() const;
    
    private:
        friend Int _add_vint_abs(const Int& lhs, const Int& rhs);
        friend Int _sub_vint_abs(const Int& lhs, const Int& rhs);
        friend Int abs(const Int& value);
    private:
        enum sign { negative, positive };
        bool m_sign = sign::positive;
        std::vector<uint32_t> m_storage = { };
    };

}

#endif // VARIABLE_INT_HPP
