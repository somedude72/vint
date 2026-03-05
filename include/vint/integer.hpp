/// This header provdes the integer class and includes various primitive
/// math functions under a single header file. Part of the vint project,
/// which is under the GPL-3.0 License.
///
/// For documentation on the API this header file exposes and its usage, please
/// see the docs at https:///somedude72.github.io/vint/api_reference/integer. 

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

/// Arbitrary precision integer class. Provides construction, comparison,
/// arithmetic, and other utilities for representing integers of arbitrary size. 
/// 
/// Example:
/// ```
/// vint::Integer n = vint::Integer("1234567890987654321");
/// n = (n++) - vint::ipow(n, 100);
/// n += (INT64_MIN + n) % INT64_MIN;
/// std::cout << n.to_string();
/// ```
class Integer {
public:
    /// Constructor. Initializes the object to zero by default. 
    Integer() : m_repr(internal::to_repr(0)) {}

    /// Constructor. Initializes the object to num. For integers over the limit
    /// for 64-bit long longs, use the `std::string` constructor. 
    ///
    /// Example: 
    ///
    /// ```
    /// vint::Integer n = 1000;
    /// vint::Integer m = 0xAA1245;
    /// ```
    Integer(const int64_t& num) : m_repr(internal::to_repr(num)) {}

    /// Constructor. Initializes the object to num, otherwise to zero if num is
    /// not a valid base-10 number. This is marked explicit to avoid
    /// accidentally doing math with strings. 
    ///
    /// Example: 
    ///
    /// ```
    /// vint::Integer n = vint::Integer("-12345678901234567890");
    /// vint::Integer m = vint::Integer("-0"); /// also works 
    /// ```
    explicit Integer(const std::string& num) : m_repr(internal::to_repr(num)) {}

    /// Casting the object to built-in boolean. Equivalent to checking if the
    /// object is not zero. Example:
    ///
    /// Example:
    ///
    /// ```
    /// vint::Integer n = 25;
    /// vint::Integer m = 0;
    /// if (m.to_bool() || n.to_bool()) {
    ///     std::cout << "It's true!";
    /// }
    /// ```
    bool to_bool() const {
        return internal::to_bool(m_repr);
    }

    /// Casting the object to built-in signed 64-bit integer. This method
    /// will cause overflow for large numbers. Use the to_string() method
    /// instead for arbitrary precision printing. 
    ///
    /// Example:
    /// ```
    /// vint::Integer n = 25;
    /// vint::Integer m = vint::Integer("-1234567890987654321");
    /// std::cout << n.to_int64(); // works
    /// std::cout << m.to_int64(); // will cause overflow
    /// ```
    int64_t to_int64() const {
        return internal::to_int(m_repr);
    }

    /// Casting the object to built-in std::string without causing overflow. 
    ///
    /// Example:
    /// ```
    /// vint::Integer n = 25;
    /// vint::Integer m = vint::Integer("1234567890987654321");
    /// std::cout << n.to_string(); // works
    /// std::cout << m.to_string(); // also works
    /// ```
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

/// Urinary addition. Returns value itself in O(1)
/// 
/// Example:
/// ```
/// vint::Integer a = 10;
/// vint::Integer b = +a;
/// std::cout << b.to_string(); // <- prints 10
/// ```
inline Integer operator+(const Integer& val) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& val_repr = internal::IntReprAccess::get(val);
    ret_repr = +val_repr;
    return ret;
}

/// Urinary subtraction. Returns the opposite number in O(1)
///
/// Example:
/// ```
/// vint::Integer a = 10;
/// vint::Integer b = -a;
/// std::cout << b.to_string(); /// <- prints -10
/// ```
inline Integer operator-(const Integer& val) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& val_repr = internal::IntReprAccess::get(val);
    ret_repr = -val_repr;
    return ret;
}

/// Arbitrary precision addition. Returns the sum of both numbers in O(n), where
/// n is the number of limbs in base_t. 
///
/// Example: 
/// ```
/// vint::Integer a = vint::Integer("12345678901234567890");
/// vint::Integer b = vint::Integer("1029384756574839201");
/// std::cout << (a + b).to_string(); /// <- prints 13375063657809407091
/// ```
inline Integer operator+(const Integer& lhs, const Integer& rhs) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    ret_repr = lhs_repr + rhs_repr;
    return ret;
}

/// Arbitrary precision subtractions. Returns the sum of both numbers in O(n),
/// where n is the number of limbs in base_t.
///
/// Example: 
/// ```
/// vint::Integer a = vint::Integer("-12345678901234567890");
/// vint::Integer b = vint::Integer("1029384756574839201");
/// std::cout << (a - b).to_string(); /// <- prints -13375063657809407091
/// ```
inline Integer operator-(const Integer& lhs, const Integer& rhs) {
    Integer ret;
    auto& ret_repr = internal::IntReprAccess::get(ret);
    auto& lhs_repr = internal::IntReprAccess::get(lhs);
    auto& rhs_repr = internal::IntReprAccess::get(rhs);
    ret_repr = lhs_repr - rhs_repr;
    return ret;
}

/// Arbitrary precision multiplication. Returns the product of both numbers in
/// O(n^1.465), where n is the number of base type digits. 
///
/// Example: 
/// ```
/// vint::Integer a = vint::Integer("123456123456");
/// vint::Integer b = vint::Integer("654321654321");
/// std::cout << (a * b).to_string(); /// <- prints 80780014935787531853376
/// ```
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