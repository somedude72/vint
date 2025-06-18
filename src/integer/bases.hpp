/**
 * This header file exposes functions that help with the internal
 * conversion between the regular c++ types (uint64_t, std::string)
 * to an array of digits stored in base 2^32 (storage type).
 */

#ifndef BASES_HPP
#define BASES_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace vint {
    void ll_to_storage(int64_t number, std::vector<uint32_t>& storage);
    void str_to_storage(std::string number, std::vector<uint32_t>& storage);
    
    int64_t storage_to_ll(const std::vector<uint32_t>& storage, bool negative);
    std::string storage_to_str(const std::vector<uint32_t>& storage, bool negative);
}

#endif // BASES_HPP
