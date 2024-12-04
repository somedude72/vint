#include "vint/math.hpp"
#include "vint/integer.hpp"

namespace vint {
    Integer abs(const Integer& value) {
        if (value < 0)
            return -value;
        return value;
    }
}
