// Constructor implementation for vint::Int
// This file contains definition for declarations
// in variable_int.hpp

#include <cstdlib>
#include <cstdint>
#include <vector>
#include "vectors.hpp"
#include "variable_int.hpp"

namespace vint {

    Int::Int() = default;

    Int::Int(int64_t number) {
        if (number < 0)
            m_sign = sign::negative;
        if (number == 0)
            m_storage.push_back(0);
        number = std::abs(number);
        while (number) {
            m_storage.push_back(number % ((int64_t) (UINT32_MAX) + 1));
            number /= ((int64_t) (UINT32_MAX) + 1);
        }
    }

    Int::Int(const std::string& number) {
        if (number.empty())
            m_storage = { 0 };
        if (number == "-0")
            m_storage = { 0 };
        if (number[0] == '-')
            m_sign = sign::negative;
            
        size_t num_start = (m_sign == sign::negative) ? 1 : 0;
        std::vector<uint8_t> num_vec(number.size() - num_start);
        for (size_t i = num_start; i < number.size(); i++)
            num_vec[i - num_start] = number[i] - '0';
    
        while (!num_vec.empty()) {
            m_storage.push_back(divide_vectors(num_vec, (uint64_t) (UINT32_MAX) + 1));
        }
    }

}
