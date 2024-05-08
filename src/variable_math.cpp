#include "variable_int.hpp"
#include "variable_math.hpp"

namespace vint {

    Int abs(const Int& value) {
        Int ret = value;
        ret.m_sign = Int::sign::positive;
        return ret;
    }

}