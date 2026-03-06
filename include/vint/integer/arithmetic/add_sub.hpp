// This header provdes the internal implementation for the integer class. Do not
// include this header file on its own. Part of the vint project, which is
// distributed under the GPL-3.0 License. 

#ifndef VINT_INTEGER_IMPL_ARITHMETIC_ADD_SUB
#define VINT_INTEGER_IMPL_ARITHMETIC_ADD_SUB

#include "../base.hpp"
#include "../utils.hpp"

namespace vint {
namespace internal {

IntRepr operator+(const IntRepr&, const IntRepr&);
IntRepr operator-(const IntRepr&, const IntRepr&);

static inline storage_t add_storage(const storage_t& lhs, const storage_t& rhs) {
    const size_t na = lhs.size();
    const size_t nb = rhs.size();
    const size_t n = std::max(na, nb);
    
    uint64_t carry = 0;
    storage_t result(n);

    for (size_t i = 0; i < n; i++) {
        const uint64_t ai = (i < na) ? lhs[i] : 0;
        const uint64_t bi = (i < nb) ? rhs[i] : 0;
        uint64_t sum = ai + bi + carry;
        result[i] = static_cast<base_t>(sum & (INTEGER_BASE - 1));
        carry = sum >= INTEGER_BASE;
    }

    if (carry) {
        result.push_back(1);
    }

    return result;
}

static inline storage_t sub_storage(const storage_t& lhs, const storage_t& rhs) {
    const size_t na = lhs.size();
    const size_t nb = rhs.size();
    const size_t n = na;

    uint64_t borrow = 0;
    storage_t result(n);

    for (size_t i = 0; i < n; i++) {
        uint64_t ai = (i < na) ? lhs[i] : 0;
        uint64_t bi = (i < nb) ? rhs[i] : 0;
        uint64_t diff = ai - bi - borrow;
        result[i] = static_cast<base_t>(diff & (INTEGER_BASE - 1));
        borrow = ai < (bi + borrow);
    }

    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    }
    
    return result;
}

inline IntRepr operator+(const IntRepr& lhs, const IntRepr& rhs) {
    IntRepr ret;

    if (!rhs.positive) {
        ret = lhs - abs(rhs);
    } else if (lhs.positive) {
        ret.positive = true;
        ret.limbs = add_storage(lhs.limbs, rhs.limbs);
    } else if (abs(lhs) > abs(rhs)) {
        ret.positive = false;
        ret.limbs = sub_storage(lhs.limbs, rhs.limbs);
    } else if (abs(lhs) < abs(rhs)) {
        ret.positive = true;
        ret.limbs = sub_storage(rhs.limbs, lhs.limbs);
    }

    normalize_zero(ret);
    return ret;
}

inline IntRepr operator-(const IntRepr& lhs, const IntRepr& rhs) {
    IntRepr ret;

    if (!rhs.positive) {
        ret = lhs + abs(rhs);
    } else if (!lhs.positive) {
        ret.positive = false;
        ret.limbs = add_storage(lhs.limbs, rhs.limbs);
    } else if (abs(lhs) > abs(rhs)) {
        ret.positive = true;
        ret.limbs = sub_storage(lhs.limbs, rhs.limbs);
    } else if (abs(lhs) < abs(rhs)) {
        ret.positive = false;
        ret.limbs = sub_storage(rhs.limbs, lhs.limbs);
    }

    normalize_zero(ret);
    return ret;
}

inline IntRepr operator+(const IntRepr& val) {
    return val;
}

inline IntRepr operator-(const IntRepr& val) {
    IntRepr ret = val;
    ret.positive = !val.positive;
    return ret;
}

}
}

#endif // VINT_INTEGER_IMPL_ARITHMETIC_ADD_SUB