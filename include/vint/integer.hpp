#ifndef VINT_INTEGER_HPP
#define VINT_INTEGER_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

namespace vint {

    class Integer {
    public:
        Integer();
        Integer(const int64_t& number);
        Integer(const std::string& number);

        bool to_bool() const;
        int32_t to_int() const;
        int64_t to_long_long() const;
        std::string to_string() const;

        size_t bytes() const;

    public:
        Integer operator+(const Integer& rhs) const;
        Integer operator-(const Integer& rhs) const;
        Integer operator*(const Integer& rhs) const;

        bool operator<(const Integer& comp) const;
        bool operator>(const Integer& comp) const;
        bool operator<=(const Integer& comp) const;
        bool operator>=(const Integer& comp) const;
        bool operator==(const Integer& comp) const;
        Integer operator-() const;

        const std::vector<uint32_t>& raw() const;

    private:
        enum sign { positive = 0, negative = 1 };
        bool m_sign = positive;
        std::vector<uint32_t> m_storage = { };
    };
    
}

#endif // VINT_INTEGER_HPP
