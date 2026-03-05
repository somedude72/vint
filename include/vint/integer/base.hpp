// This header provdes the internal implementation for the integer class. Do not
// include this header file on its own. Part of the vint project, which is under
// the GPL-3.0 License. 

#ifndef VINT_INTEGER_IMPL_REPR
#define VINT_INTEGER_IMPL_REPR

#include <cstdint>
#include <limits>
#include <vector>

namespace vint {
namespace internal {

using base_t = uint32_t;
using storage_t = std::vector<base_t>;

static constexpr uint64_t INTEGER_BASE = (uint64_t) std::numeric_limits<base_t>::max() + 1;
static constexpr uint32_t INTEGER_BASE_DIGITS = std::numeric_limits<base_t>::digits;
static constexpr uint32_t TOOM_MUL_THRESHOLD = 100; // Limb size
static constexpr uint32_t CONQ_DIV_THRESHOLD = 100; // Limb size

/// Internal representation of arbitrary precision integer. Three one bit
/// booleans stores the sign, inf, and nan. the vector of storage_t stores the
/// limbs in little-endian (least significant limbs first).
struct IntRepr {
    storage_t limbs = { };
    bool positive = false;
};

}
}

#endif // VINT_INTEGER_IMPL_REPR