// Constructor implementation for vint::Int
// This file contains definition for declarations
// in variable_int.hpp

#include <cstdlib>
#include <cstdint>
#include <vector>
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

    // Int::Int(const std::string& number) {
    //     TODO: IMPLEMENT STRING CONSTRUCTOR
    // }

}
