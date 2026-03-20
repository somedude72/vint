// This header provdes the internal implementation for the integer class. Do not
// include this header file on its own. Part of the vint project, which is
// distributed under the GPL-3.0 License. 

#ifndef VINT_INTEGER_IMPL_CONV
#define VINT_INTEGER_IMPL_CONV

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

#include "base.hpp"

// TODO: Replace all conversion functions with ones based on exponents and
// division once fast integer exponent and division is implemented. 

namespace vint {
namespace internal {

static inline std::vector<uint8_t> add_array_helper(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b, int base = 10) {
    const size_t n = std::max(a.size(), b.size());
    std::vector<uint8_t> ret = { };
    ret.reserve(n);
    
    uint8_t carry = 0;
    for (size_t i = 0; i < n; ++i) {
        uint8_t digit1 = (i < a.size()) ? a[a.size() - 1 - i] : 0;
        uint8_t digit2 = (i < b.size()) ? b[b.size() - 1 - i] : 0;
        uint8_t sum = digit1 + digit2 + carry;
        ret.push_back(sum % base);
        carry = sum / base;
    }

    if (carry > 0) {
        ret.push_back(carry);
    }

    std::reverse(ret.begin(), ret.end());
    return ret;
}

static inline std::vector<uint8_t> mul_array_helper(const std::vector<uint8_t>& a, uint64_t b) {
    std::vector<uint64_t> temp(a.begin(), a.end());
    uint64_t prev_carry = 0;
    uint64_t curr_carry = 0;

    for (int64_t i = temp.size() - 1; i >= 0; i--) {
        temp[i] *= b;

        curr_carry = temp[i] / 10;
        temp[i] %= 10;
        temp[i] += prev_carry;

        curr_carry += (temp[i] / 10);
        temp[i] %= 10;
        prev_carry = curr_carry;
    }

    while (prev_carry) {
        temp.insert(temp.begin(), prev_carry % 10);
        prev_carry /= 10;
    }

    while (!temp.empty() && temp.front() == 0) {
        temp.erase(temp.begin());
    }

    if (temp.empty()){
        return std::vector<uint8_t> { 0 };
    } else {
        return std::vector<uint8_t>(temp.begin(), temp.end());;
    }
}

static inline uint64_t div_array_helper(std::vector<uint8_t>& a, uint64_t b) {
    uint64_t remainder = 0;

    for (auto& digit : a) {
        uint64_t dividend_part = remainder * 10 + digit;
        digit = dividend_part / b;
        remainder = dividend_part % b;
    }

    while (!a.empty() && a.front() == 0) {
        a.erase(a.begin());
    }
    
    return remainder;
}

static inline void ll_to_storage(int64_t num, storage_t& storage) {
    num = std::abs(num);

    while (num) {
        storage.push_back(num % INTEGER_BASE);
        num /= INTEGER_BASE;
    }
}

static inline void str_to_storage(std::string num, storage_t& storage) {
    const size_t num_start = num[0] == '-' ? 1 : 0;
    std::vector<uint8_t> num_vec(num.size() - num_start);

    for (size_t i = num_start; i < num.size(); i++)
        num_vec[i - num_start] = num[i] - '0';
    while (!num_vec.empty()) {
        storage.push_back(div_array_helper(num_vec, INTEGER_BASE));
    }
}

static inline int64_t storage_to_ll(const storage_t& storage) {
    int64_t ret = 0;
    int64_t power = 1;

    for (const auto& digit : storage) {
        ret += power * static_cast<int64_t>(digit);
        power *= UINT32_MAX;
    }

    return ret;
}

static inline std::string storage_to_str(const storage_t& storage) {
    std::vector<uint8_t> ret = { 0 };
    std::vector<uint8_t> power = { 1 };
    std::string result = "";

    for (const auto& digit : storage) {
        constexpr uint64_t base = static_cast<uint64_t>(UINT32_MAX) + 1;
        ret = add_array_helper(ret, mul_array_helper(power, digit));
        power = mul_array_helper(power, base);
    }

    for (const auto& digit : ret)
        result += std::to_string(digit);
    return result;
}

inline IntRepr to_repr(int64_t num) {
    IntRepr ret;
    if (num < 0)
        ret.positive = false;
    if (num == 0) {
        ret.positive = true;
        ret.limbs = { 0 };
    }

    ll_to_storage(num, ret.limbs);
    return ret;
}

inline IntRepr to_repr(const std::string& num) {
    IntRepr ret;
    if (!num.empty() && num[0] == '-')
        ret.positive = false;
    if (num.empty() || num == "-0") {
        ret.positive = true;
        ret.limbs = { 0 };
    }

    str_to_storage(num, ret.limbs);
    return ret;
}

inline bool to_bool(const IntRepr& repr) {
    return !(repr.limbs.size() == 1 && repr.limbs[0] == 0);
}

inline int64_t to_int(const IntRepr& repr) {
    int64_t ret = storage_to_ll(repr.limbs);
    return (repr.positive) ? ret : -ret;
}

inline std::string to_str(const IntRepr& repr) {
    std::string ret = storage_to_str(repr.limbs);
    return (repr.positive) ? ret : '-' + ret;
}

}
}

#endif // VINT_INTEGER_IMPL_CONV