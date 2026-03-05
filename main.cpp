#include "include/vint/integer.hpp"
#include <iostream>

using namespace vint;

int main() {
    Integer a = Integer("1123456789123456789");
    Integer b = Integer("-1987654321987654321");
    Integer c = a * a * a * a * a * a;

    std::cout << c.to_string() << std::endl;
    std::cin.get();
}