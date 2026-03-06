// This header provdes the internal implementation for the integer class. Do not
// include this header file on its own. Part of the vint project, which is
// distributed under the GPL-3.0 License. 

#ifndef VINT_INTEGER_IMPL_COMPARE
#define VINT_INTEGER_IMPL_COMPARE

#include "base.hpp"

namespace vint {
namespace internal {

inline bool operator==(const IntRepr& lhs, const IntRepr& rhs) {
    return lhs.positive == rhs.positive && lhs.limbs == rhs.limbs;
}

inline bool operator!=(const IntRepr& lhs, const IntRepr& rhs) {
    return !(lhs == rhs);
}

inline bool operator<(const IntRepr& lhs, const IntRepr& rhs) {
    if (!lhs.positive && rhs.positive)
        return true;
    if (lhs.positive && !rhs.positive)
        return false;
    if (lhs.limbs.size() < rhs.limbs.size())
        return true;
    if (rhs.limbs.size() < lhs.limbs.size())
        return false;
    for (int64_t i = (int64_t) lhs.limbs.size() - 1; i >= 0; i--) {
        if (lhs.positive && lhs.limbs[i] < rhs.limbs[i])
            return true;
        if (!lhs.positive && lhs.limbs[i] < rhs.limbs[i])
            return false;
        if (!lhs.positive && lhs.limbs[i] > rhs.limbs[i])
            return true;
        if (lhs.positive && lhs.limbs[i] > rhs.limbs[i])
            return false;
    }

    return false; // lhs == rhs
}

inline bool operator>(const IntRepr& lhs, const IntRepr& rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}

inline bool operator<=(const IntRepr& lhs, const IntRepr& rhs) {
    return !(lhs > rhs);
}

inline bool operator>=(const IntRepr& lhs, const IntRepr& rhs) {
    return !(lhs < rhs);
}

}
}

#endif // VINT_INTEGER_IMPL_COMPARE