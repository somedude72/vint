// Arithmetic operator implementation for vint::Int
// This file contains definition for declarations
// in ../include/variable_int.hpp

#include <vector>
#include "variable_int.hpp"

namespace vint {

    Int Int::operator+(const Int& rhs) const {
        Int ret;
        if (m_storage.size() > rhs.m_storage.size()) {
            int i = 0;
            for (; i < rhs.m_storage.size(); i++) {
                if (ret.m_storage.size() != i + 1)
                    ret.m_storage.push_back(0);
                if (ret.m_storage[i] != 0) { // previous carry
                    ret.m_storage[i] = m_storage[i] + rhs.m_storage[i];
                    if (ret.m_storage[i] <= m_storage[i]) // overflow (ie carry). <= in this case because we started with 1
                        ret.m_storage.push_back(1);
                } else { // no previous carry
                    ret.m_storage[i] = m_storage[i] + rhs.m_storage[i];
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
                    ret.m_storage[i] = m_storage[i] + rhs.m_storage[i] + 1;
                    if (ret.m_storage[i] <= m_storage[i]) { // overflow (ie carry). <= in this case because we started with 1
                        ret.m_storage[i]++; // add one when overflow due to base conversion
                        ret.m_storage.push_back(1);
                    }
                } else { // no previous carry
                    ret.m_storage[i] = m_storage[i] + rhs.m_storage[i];
                    if (ret.m_storage[i] < m_storage[i]) { // overflow (ie carry)
                        ret.m_storage[i]++; // add one when overflow due to base conversion
                        ret.m_storage.push_back(1);
                    }
                }
            }

            for (int j = i; j < rhs.m_storage.size(); j++) {
                ret.m_storage.push_back(m_storage[i]);
            }
        }

        return ret;
    }

    Int& Int::operator+=(const Int& rhs) {
        if (this == &rhs) {
            *this = rhs + rhs;
            return *this;
        }

        if (m_storage.size() > rhs.m_storage.size()) {
            int i = 0;
            for (; i < rhs.m_storage.size(); i++) {
                if (m_storage.size() != i + 1)
                    m_storage.push_back(0);
                if (m_storage[i] != 0) { // previous carry
                    m_storage[i] = m_storage[i] + rhs.m_storage[i];
                    if (m_storage[i] <= m_storage[i]) // overflow (ie carry). <= in this case because we started with 1
                        m_storage.push_back(1);
                } else { // no previous carry
                    m_storage[i] = m_storage[i] + rhs.m_storage[i];
                    if (m_storage[i] < m_storage[i]) // overflow (ie carry)
                        m_storage.push_back(1);
                }
            }

            for (int j = i; j < m_storage.size(); j++) {
                m_storage.push_back(m_storage[i]);
            }
        } else {
            int i = 0;
            for (; i < m_storage.size(); i++) {
                if (m_storage.size() != i + 1)
                    m_storage.push_back(0);
                if (m_storage[i] != 0) { // previous carry
                    m_storage[i] = m_storage[i] + rhs.m_storage[i] + 1;
                    if (m_storage[i] <= m_storage[i]) { // overflow (ie carry). <= in this case because we started with 1
                        m_storage[i]++; // add one when overflow due to base conversion
                        m_storage.push_back(1);
                    }
                } else { // no previous carry
                    m_storage[i] = m_storage[i] + rhs.m_storage[i];
                    if (m_storage[i] < m_storage[i]) { // overflow (ie carry)
                        m_storage[i]++; // add one when overflow due to base conversion
                        m_storage.push_back(1);
                    }
                }
            }

            for (int j = i; j < rhs.m_storage.size(); j++) {
                m_storage.push_back(m_storage[i]);
            }
        }

        return *this;
    }

    Int Int::operator++(int) {
        Int temp = *this;
        if (m_storage[0] < UINT32_MAX - 1) {
            m_storage[0]++;
            return temp;
        }

        for (int i = 0; i < m_storage.size(); i++) {
            if (m_storage[i] >= UINT32_MAX - 1 && i != m_storage.size() - 1) {
                m_storage[i]++;
                continue;
            }

            if (m_storage[i] < UINT32_MAX - 1 && i != m_storage.size() - 1) {
                m_storage[i]++;
                break;
            }

            if (m_storage[i] < UINT32_MAX - 1) {
                m_storage[i]++;
                break;
            } else {
                m_storage[i] = 0;
                m_storage.push_back(1);
                break;
            }
        }

        return temp;
    }

    Int Int::operator++() {
        if (m_storage[0] < UINT32_MAX - 1) {
            m_storage[0]++;
            return *this;
        }

        for (int i = 0; i < m_storage.size(); i++) {
            if (m_storage[i] >= UINT32_MAX - 1 && i != m_storage.size() - 1) {
                m_storage[i]++;
                continue;
            }

            if (m_storage[i] < UINT32_MAX - 1 && i != m_storage.size() - 1) {
                m_storage[i]++;
                break;
            }

            if (m_storage[i] < UINT32_MAX - 1) {
                m_storage[i]++;
                break;
            } else {
                m_storage[i] = 0;
                m_storage.push_back(1);
                break;
            }
        }

        return *this;
    }

}
