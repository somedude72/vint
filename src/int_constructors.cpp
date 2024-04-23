// Constructor implementation for vint::Int
// This file contains definition for declarations
// in ../include/variable_int.hpp

#include <vector>
#include <cstdint>
#include "variable_int.hpp"

namespace vint {

    Int::Int() = default;

    Int::Int(int64_t number) {
        if (number < 0)
            m_sign = sign::negative;
        if (number == 0)
            m_storage.push_back(0);
        while (number) {
            m_storage.push_back((uint32_t)(number % Int::STORAGE_BASE));
            number /= Int::STORAGE_BASE;
        }
    }

    // Int::Int(const std::string& number) {
    //     [TODO] IMPLEMENT STRING CONSTRUCTOR
    // }

}
