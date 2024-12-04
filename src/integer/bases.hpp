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
    void int_to_storage(int64_t number, std::vector<uint32_t>& storage);
    void str_to_storage(std::string number, std::vector<uint32_t>& storage);
    
    void storage_to_int(const std::vector<uint32_t>& storage, int64_t& number, bool negative);
    void storage_to_str(const std::vector<uint32_t>& storage, std::string& number, bool negative);
}

#endif // BASES_HPP
