// Arithmetic operator implementation for vint::Int
// This file contains definition for declarations
// in ../include/variable_int.hpp

#include <vector>
#include <iostream>

#include "variable_int.hpp"

template <typename T>
static void pv(const std::vector<T>& v) {
    std::cout << "[";
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << ", ";
    std::cout << "\b\b]";
}

namespace vint {

    Int Int::operator+(const Int& other) const {
        Int ret;
        if (m_storage.size() > other.m_storage.size()) {
            int i = 0;
            for (; i < other.m_storage.size(); i++) {
                if (ret.m_storage.size() != i + 1)
                    ret.m_storage.push_back(0);
                if (ret.m_storage[i] != 0) { // previous carry
                    ret.m_storage[i] = m_storage[i] + other.m_storage[i];
                    if (ret.m_storage[i] <= m_storage[i]) // overflow (ie carry). <= in this case because we started with 1
                        ret.m_storage.push_back(1);
                } else { // no previous carry
                    ret.m_storage[i] = m_storage[i] + other.m_storage[i];
                    if (ret.m_storage[i] < m_storage[i]) // overflow (ie carry)
                        ret.m_storage.push_back(1);
                }
            }

            for (int j = i; j < m_storage.size(); j++) {
                ret.m_storage.push_back(m_storage[i]);
            }
        } else {
            int i = 0;
            for (; i < m_storage.size(); i++) {
                if (ret.m_storage.size() != i + 1)
                    ret.m_storage.push_back(0);
                if (ret.m_storage[i] != 0) { // previous carry
                    ret.m_storage[i] = m_storage[i] + other.m_storage[i] + 1;
                    if (ret.m_storage[i] <= m_storage[i]) { // overflow (ie carry). <= in this case because we started with 1
                        ret.m_storage[i]++; // add one when overflow due to base conversion
                        ret.m_storage.push_back(1);
                    }
                } else { // no previous carry
                    ret.m_storage[i] = m_storage[i] + other.m_storage[i];
                    if (ret.m_storage[i] < m_storage[i]) { // overflow (ie carry)
                        ret.m_storage[i]++; // add one when overflow due to base conversion
                        ret.m_storage.push_back(1);
                    }
                }
            }

            for (int j = i; j < other.m_storage.size(); j++) {
                ret.m_storage.push_back(m_storage[i]);
            }
        }

        return ret;
    }

}
