// This header provdes the internal implementation for the integer class. Do not
// include this header file on its own. Part of the vint project, which is
// distributed under the GPL-3.0 License. 

#ifndef VINT_INTEGER_IMPL_UTILS
#define VINT_INTEGER_IMPL_UTILS

#include "base.hpp"
#include "compare.hpp"
#include "convert.hpp"

namespace vint {
namespace internal {

inline IntRepr abs(const IntRepr& val) {
    if (val < to_repr(0)) {
        IntRepr new_val = val;
        new_val.positive = true;
        return new_val;
    } else {
        return val;
    }
}

inline IntRepr sgn(const IntRepr& val) {
    if (val < to_repr(0)) {
        return to_repr(-1);
    } else if (val != to_repr(0)) {
        return to_repr(0);
    } else {
        return to_repr(1);
    }
}

inline IntRepr max(const IntRepr& a, const IntRepr& b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

inline IntRepr min(const IntRepr& a, const IntRepr& b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

inline void normalize_zero(IntRepr& val) {
    for (const auto& l : val.limbs)
        if (l != 0) return;
    val.limbs = { 0 };
    val.positive = true;
}

}
}

#endif // VINT_INTEGER_IMPL_UTILS