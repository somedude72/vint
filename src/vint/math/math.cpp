#include "vint/integer.hpp"
#include "vint/math.hpp"

namespace vint {

    Int abs(const Int& value) {
        Int ret = value;
        ret.m_sign = Int::sign::positive;
        return ret;
    }

}
