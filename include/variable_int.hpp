#ifndef VARIABLE_INT_HPP
#define VARIABLE_INT_HPP

#include <vector>
#include <cstdint>
#include <cstdlib>

namespace vint {

    /**
     * @brief
     * An arbitrary precision integer type in C++.
     *
     * @note
     * All basic logical and binary operators have been implemented. See individual
     * method documentation for more details. This class has been written to behave
     * like a regular C++ integer.
     *
     * @details
     * Implemented similar to Python's `int` object. The integer itself is stored
     * in base `2^32` (or base `4,294,967,296`) in a vector of `uint32_t`, where
     * each element in the vector represents a digit. For more information, see
     * [this article](https://rushter.com/blog/python-integer-implementation/) for
     * details on how Python's arbitrary integer is implemented, as the overall
     * idea/concept is the same.
     */
    class Int {
    public: /* Class constructors */

        /**
         * @brief
         * Default class constructor, initializes a `Int` object with the
         * represented number initialized to 0 and sign to positive.
         */
        Int();

        /**
         * @brief
         * Initializes a `Int` object with a number.
         *
         * @param number
         * The number that the object shall hold. This must be within signed 64-bit
         * integer. If a bigger initial number is required, use the `std::string`
         * constructor instead.
         */
        Int(int64_t number);

        /**
         * @brief
         * Constructs a new instance of `Int` with a number. [UNIMPLEMENTED]
         *
         * @param number
         * The number (in string) to construct the instance with. This method is
         * significantly slower than using the long long constructor, however it is
         * integer overflow-proof, meaning that any arbitrarily large number could
         * be used here.
         */
        // Int(const std::string& number);

    public: /* Type conversion operators */

        /**
         * @brief
         * int64_t conversion operator.
         *
         * This operator has not been marked explicit because this class is
         * written to behave like a regular C++ integer.
         */
        operator int64_t() const;

        /**
         * @brief
         * std::string convertion operator.
         *
         * Converts the `Int` instance into an std::string. This method is
         * significantly more expensive to run, however it is integer overflow-proof.
         *
         * @details
         * In order to make this function overflow-proof, complicated (and expensive)
         * vector operations had to be implemented in place of the regular integer
         * operators when using the int64_t conversion operator. Because of this, this
         * method will not scale well as the size of the integer gets larger.
         *
         * To address this issue (which is my laziness of not optimizing), you can write
         * your own `to_string` conversion operator. You can access the underlying storage
         * vector by using the `raw()` method of this class. From there, have fun converting
         * a vector representing a number stored in base 2^32 (where each element represents
         * a digit) into a string in base 10.
         */
        std::string to_string() const;

        /**
         * @brief
         * Getter for the size of the raw array
         *
         * @returns
         * A `size_t` representing the size of the raw array
         */
        size_t elements() const;

        /**
         * @brief
         * Computes the total size (in bytes) allocated
         *
         * @returns
         * A `size_t` representing the total bytes used by a Int object.
         */
        size_t size() const;

        /**
         * @brief
         * Getter for the raw array
         *
         * @returns
         * An `std::vector` of unsigned 32 byte integer; actual storable space is
         * 2^32 - 1. Each element in the vector is a digit in base 2^32. This
         * method returns the underlying storage vector.
         */
        std::vector<uint32_t>& raw();

    public: /* Comparison operators [UNIMPLEMENTED] */

        // bool operator==(const Int& other);

        // bool operator<=(const Int& other);

        // bool operator>=(const Int& other);

        // bool operator<(const Int& other);

        // bool operator>(const Int& other);

        // bool operator!=(const Int& other);

        // bool operator!();

    public: /* Arithmetic operators */

        /**
         * @brief
         * Addition operator
         *
         * @param other
         * The number to be added to the current number
         *
         * @returns
         * The result of the addition in an vint::Int object
         */
        Int operator+(const Int& other) const;

        // Int operator-(const Int& other) const;

        // Int operator*(const Int& other);

        // Int operator/(const Int& other);

        // Int operator%(const Int& other);

    private:
        static constexpr uint32_t STORAGE_BASE = 4294967295; // (2^32 - 1)
        enum sign { negative, positive };
        bool m_sign = sign::positive;
        std::vector<uint32_t> m_storage = {}; // Least significant digit first.
    };                                       // Stored in base 2^32

}

#endif // VARIABLE_INT_HPP
