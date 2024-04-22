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

std::vector<uint8_t> multiply_vectors(const std::vector<uint8_t>& num_one,
                                      const std::vector<uint8_t>& num_two) {
    std::vector<std::vector<uint8_t>> sum(num_two.size());
    for (size_t i = 0; i < sum.size(); i++)
        for (size_t j = 0; j < i; j++)
            sum[i].push_back(0);

    for (int64_t i = num_two.size() - 1; i >= 0; i--) {
        for (int64_t j = num_one.size() - 1; j >= 0; j--)
            sum[num_two.size() - i - 1].insert(
                sum[num_two.size() - i - 1].begin(),
                num_two[i] * num_one[j]
            );
        process_overflow(sum[num_two.size() - i - 1]);
    }

    for (size_t i = 1; i < sum.size(); i++)
        add_vectors(sum[0], std::move(sum[i]));
    while (sum[0][0] == 0 && sum[0].size() != 1)
        sum[0].erase(sum[0].begin());
    return sum[0];
}
