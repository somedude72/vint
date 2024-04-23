// Implementation file for voperators.hpp

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

#include "voperators.hpp"

std::vector<uint8_t> int_to_vec(uint32_t integer) {
    std::vector<uint8_t> ret = {};
    std::string in_string = std::to_string(integer);
    for (const auto& character : in_string)
        ret.push_back(character - '0');
    return ret;
}

void perform_addition(std::vector<uint8_t>& num_two,
                      std::vector<uint8_t>& num_one) {
    for (size_t i = 0; i < num_one.size(); i++)
        num_one[i] += num_two[i];
}

void process_overflow(std::vector<uint8_t>& vector,
                      const int32_t base) {
    std::reverse(vector.begin(), vector.end());
    for (size_t i = 0; i < vector.size(); i++) {
        if (i == vector.size() - 1 && vector[i] >= base)
            vector.push_back(0);
        while (vector[i] >= base) {
            vector[i] -= base;
            vector[i + 1]++;
        }
    }
    std::reverse(vector.begin(), vector.end());
}

void align_vectors(std::vector<uint8_t>& v1,
                   std::vector<uint8_t>& v2) {
    const auto size_one = (int64_t)(v1.size());
    const auto size_two = (int64_t)(v2.size());
    const auto diff = (size_t)(std::abs(size_one - size_two));
    for (size_t i = 0; i < diff; i++) {
        if (v1.size() < v2.size())
            v1.insert(v1.begin(), 0);
        if (v2.size() < v1.size())
            v2.insert(v2.begin(), 0);
    }
}

void align_vectors(std::vector<uint32_t>& v1,
                   std::vector<uint32_t>& v2) {
    const auto size_one = (int64_t)(v1.size());
    const auto size_two = (int64_t)(v2.size());
    const auto diff = (size_t)(std::abs(size_one - size_two));
    for (size_t i = 0; i < diff; i++) {
        if (v1.size() < v2.size())
            v1.insert(v1.begin(), 0);
        if (v2.size() < v1.size())
            v2.insert(v2.begin(), 0);
    }
}

void add_vectors(std::vector<uint8_t>& num_one,
                 std::vector<uint8_t>&& num_two) {
    align_vectors(num_two, num_one);
    perform_addition(num_two, num_one);
    process_overflow(num_one);
}

std::vector<uint8_t> multiply_vectors(const std::vector<uint8_t>& num1,
                                      const std::vector<uint8_t>& num2) {
    int n = num1.size();
    int m = num2.size();
    const int BASE = 10;
    std::vector<uint8_t> result(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = num1[i] * num2[j];
            int sum = mul + result[i + j + 1];
            result[i + j] += sum / BASE;
            result[i + j + 1] = sum % BASE;
        }
    }

    int i = 0;
    while (i < n + m && result[i] == 0)
        i++;
    if (i == n + m)
        return { 0 };
    return std::vector<uint8_t>(result.begin() + i, result.end());
}
