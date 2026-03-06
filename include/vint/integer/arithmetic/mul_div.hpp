// This header provdes the internal implementation for the integer class. Do not
// include this header file on its own. Part of the vint project, which is
// distributed under the GPL-3.0 License. 

#ifndef VINT_INTEGER_IMPL_ARITHMETIC_MUL_DIV
#define VINT_INTEGER_IMPL_ARITHMETIC_MUL_DIV

#include "../base.hpp"
#include "../utils.hpp"
#include "add_sub.hpp"

namespace vint {
namespace internal {

IntRepr operator*(const IntRepr &lhs, const IntRepr &rhs);
IntRepr operator/(const IntRepr &lhs, const IntRepr &rhs);

inline storage_t mul_storage_norm(const storage_t &lhs, const storage_t &rhs) {
  // Schoolbook multiplication algorithm.
  //
  // For each pair of indices (i, j), the quantity lhs[i] * rhs[i] contributes
  // to digit i + j in the product. By iterating through all pairs of (i,j)
  // and carrying as appropriate, we arrive at the answer.
  //
  // This algorithm runs in O(n^2)

  const size_t na = lhs.size();
  const size_t nb = rhs.size();
  storage_t result(na + nb);

  for (size_t i = 0; i < na; i++) {
    uint64_t carry = 0;

    for (size_t j = 0; j < nb; j++) {
      uint64_t ai = lhs[i];
      uint64_t bj = rhs[j];
      uint64_t prod = ai * bj;
      uint64_t cur = result[i + j];
      uint64_t sum = cur + prod + carry;

      result[i + j] = static_cast<base_t>(sum & (INTEGER_BASE - 1));
      carry = sum >> INTEGER_BASE_DIGITS;
    }

    for (size_t j = i + nb; carry; j++) {
      uint64_t sum = (uint64_t)result[j] + carry;
      result[j] = static_cast<base_t>(sum & (INTEGER_BASE - 1));
      carry = sum >> INTEGER_BASE_DIGITS;
    }
  }

  while (result.size() > 1 && result.back() == 0) {
    result.pop_back();
  }

  return result;
}

inline storage_t mul_storage_toom(const storage_t &lhs, const storage_t &rhs) {
  // Toom-3 symmetrical multiplication in O(n^1.465)
  // We split the storage vectors into two polynomials:
  //  - p(x) = a0 * x^2 + a1 * x + a2
  //  - q(x) = b0 * x^2 + b1 * x + b2
  // Our objective is to interpolate the result polynomial:
  //  - r(x) = c0 * x^4 + c1 * x^3 + c2 * x^2 + c3 * x + c4
  //
  // We can do this by evaluating resulting polynomials at 0, 1, -1, 2, inf to
  // find points on final resulting polynomial r(x), where r(a) = p(a) * q(a).
  // Here, we recursively call Toom-3 multiplication, and by doing so we
  // reduce the time complexity.
  //
  // Finally, we evaluate r(x) at x = (base) ^ (split size) to recover the
  // product. Since x is evaluated at our base, we simplify this part to
  // shifting the coefficients by the split size.
  //
  // This algorithm runs in O(n^1.465)

  const size_t na = lhs.size();
  const size_t nb = rhs.size();
  size_t split = (std::max(na, nb) / 3) + 1;

  if (std::min(na, nb) < split) {
    // TODO: Logic for uneven Toom multiplication (3:1)
  } else if (std::min(na, nb) < (2 * split)) {
    // TODO: Logic for uneven Toom multiplication (2:1)
  }

  // Splitting
  IntRepr a0;
  a0.limbs = storage_t(lhs.begin() + 2 * split, lhs.end());
  IntRepr a1;
  a1.limbs = storage_t(lhs.begin() + split, lhs.begin() + 2 * split);
  IntRepr a2;
  a2.limbs = storage_t(lhs.begin(), lhs.begin() + split);
  IntRepr b0;
  b0.limbs = storage_t(rhs.begin() + 2 * split, rhs.end());
  IntRepr b1;
  b1.limbs = storage_t(rhs.begin() + split, rhs.begin() + 2 * split);
  IntRepr b2;
  b2.limbs = storage_t(rhs.begin(), rhs.begin() + split);

  // Evaluating
  IntRepr p0 = a2;                                     // p(0)
  IntRepr p1 = a0 + a2 + a1;                           // p(1)
  IntRepr p2 = a0 + a2 - a1;                           // p(-1)
  IntRepr p3 = to_repr(4) * a0 + to_repr(2) * a1 + a2; // p(2)
  IntRepr p4 = a0;                                     // p(inf)
  IntRepr q0 = b2;                                     // q(0)
  IntRepr q1 = b0 + b2 + b1;                           // q(1)
  IntRepr q2 = b0 + b2 - b1;                           // q(-1)
  IntRepr q3 = to_repr(4) * b0 + to_repr(2) * b1 + b2; // q(2)
  IntRepr q4 = b0;                                     // q(inf)
  IntRepr r0 = p0 * q0;                                // r(0)
  IntRepr r1 = p1 * q1;                                // r(1)
  IntRepr r2 = p2 * q2;                                // r(-1)
  IntRepr r3 = p3 * q3;                                // r(2)
  IntRepr r4 = p4 * q4;                                // r(inf)

  // Coefficient interpolation
  IntRepr i0 = r1 + r2; // intermediate result (optimization)
  IntRepr i1 = r1 - r2; // intermediate result (optimization)
  IntRepr i2 = r3 - r0; // intermediate result (optimization)
  IntRepr c0 = r0;
  IntRepr c4 = r4;
  IntRepr c2 = (i0 / to_repr(2)) - r0 - c4;
  IntRepr c1 = (i1 / to_repr(2)) - (i2 / to_repr(6)) - c2;
  IntRepr c3 = (i2 / to_repr(6)) - (i1 / to_repr(2)) - c4;

  // Shifting
}

inline storage_t div_storage_norm(const storage_t &lhs, const storage_t &rhs) {
  const size_t na = lhs.size();
  const size_t nb = rhs.size();

  storage_t result = {};
  storage_t remainder = {};
  result.reserve(na - nb);

  for (int64_t i = na - 1; i >= 0; i--) {
    uint32_t guess = rhs[i];
    // TODO
  }
}

inline storage_t div_storage_conq(const storage_t &lhs, const storage_t &rhs) {
  // TODO
}

inline IntRepr operator*(const IntRepr &lhs, const IntRepr &rhs) {
  IntRepr ret;
  ret.positive = (lhs.positive == rhs.positive);

  const size_t lhs_size = lhs.limbs.size();
  const size_t rhs_size = rhs.limbs.size();
  const size_t n = lhs_size + rhs_size;

  ret.limbs = (n >= TOOM_MUL_THRESHOLD)
                  ? mul_storage_toom(lhs.limbs, rhs.limbs)
                  : mul_storage_norm(lhs.limbs, rhs.limbs);
  normalize_zero(ret);
  return ret;
}

inline IntRepr operator/(const IntRepr &lhs, const IntRepr &rhs) {
  IntRepr ret;
  ret.positive = (lhs.positive == rhs.positive);

  const size_t n = lhs.limbs.size();
  ret.limbs = (n >= CONQ_DIV_THRESHOLD)
                  ? div_storage_conq(lhs.limbs, rhs.limbs)
                  : div_storage_norm(lhs.limbs, rhs.limbs);
  normalize_zero(ret);
  return ret;
}

} // namespace internal
} // namespace vint

#endif // VINT_INTEGER_IMPL_ARITHMETIC_MUL_DIV