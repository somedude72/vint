// This header provdes the integer class and includes various primitive
// math functions under a single header file. Part of the vint project,
// which is distributed under the GPL-3.0 License. 
//
// For documentation on the API this header file exposes and its usage, please
// see the docs at https://somedude72.github.io/vint/api_reference/integer. 
//
// Copyright (C) 2026 Zichen <connect@withzichen.com>

#ifndef VINT_INTEGER_HPP
#define VINT_INTEGER_HPP

#include <string>
#include <cstdint>

#include "integer/base.hpp"
#include "integer/convert.hpp"
#include "integer/compare.hpp"
#include "integer/arithmetic/add_sub.hpp"
#include "integer/arithmetic/mul_div.hpp"
#include "integer/utils.hpp"

namespace vint {

namespace internal { struct IntReprAccess; }

class Integer {
public:
    Integer() {
        m_repr = internal::to_repr(0);
    }

    Integer(const int64_t& num) {
        m_repr = internal::to_repr(num);
    }

    explicit Integer(const std::string& num) {
        m_repr = internal::to_repr(num);
    }

    bool to_bool() const {
        return internal::to_bool(m_repr);
    }

    int64_t to_int64() const {
        return internal::to_int(m_repr);
    }

    std::string to_string() const {
        return internal::to_str(m_repr);
    }

private:
    friend struct internal::IntReprAccess; 
    internal::IntRepr m_repr;
};

struct internal::IntReprAccess {
    static internal::IntRepr& get(Integer& x) { return x.m_repr; }
    static const internal::IntRepr& get(const Integer& x) { return x.m_repr; }
};

inline Integer operator+(const Integer& val) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& val_repr = internal::IntReprAccess::get(val);
    ret_repr = +val_repr;
    return ret;
}

inline Integer operator-(const Integer& val) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& val_repr = internal::IntReprAccess::get(val);
    ret_repr = -val_repr;
    return ret;
}

inline Integer operator+(const Integer& lhs, const Integer& rhs) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    ret_repr = lhs_repr + rhs_repr;
    return ret;
}

inline Integer operator-(const Integer& lhs, const Integer& rhs) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    ret_repr = lhs_repr - rhs_repr;
    return ret;
}

inline Integer operator*(const Integer& lhs, const Integer& rhs) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    ret_repr = lhs_repr * rhs_repr;
    return ret;
}

inline Integer operator/(const Integer& lhs, const Integer& rhs) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    ret_repr = lhs_repr / rhs_repr;
    return ret;
}

inline bool operator<(const Integer& lhs, const Integer& rhs) {
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    return lhs_repr < rhs_repr;
}

inline bool operator>(const Integer& lhs, const Integer& rhs) {
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    return lhs_repr > rhs_repr;
}

inline bool operator<=(const Integer& lhs, const Integer& rhs) {
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    return lhs_repr <= rhs_repr;
}

inline bool operator>=(const Integer& lhs, const Integer& rhs) {
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    return lhs_repr >= rhs_repr;
}

inline bool operator==(const Integer& lhs, const Integer& rhs) {
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    return lhs_repr == rhs_repr;
}

inline bool operator!=(const Integer& lhs, const Integer& rhs) {
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    return lhs_repr != rhs_repr;
}

inline Integer abs(const Integer& val) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& val_repr = internal::IntReprAccess::get(val);
    ret_repr = internal::abs(val_repr);
    return ret;
}

inline Integer sgn(const Integer& val) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& val_repr = internal::IntReprAccess::get(val);
    ret_repr = internal::sgn(val_repr);
    return ret;
}

inline Integer max(const Integer& a, const Integer& b) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& a_repr = internal::IntReprAccess::get(a);
    auto& b_repr = internal::IntReprAccess::get(b);
    ret_repr = internal::max(a_repr, b_repr);
    return ret;
}

inline Integer min(const Integer& a, const Integer& b) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& a_repr = internal::IntReprAccess::get(a);
    auto& b_repr = internal::IntReprAccess::get(b);
    ret_repr = internal::min(a_repr, b_repr);
    return ret;
}

Integer ipow(const Integer& base, const Integer& exp);
Integer fact(const Integer& val);

}

#endif // VINT_INTEGER_HPP