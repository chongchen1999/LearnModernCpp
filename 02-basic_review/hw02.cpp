#include <iostream>
#include <cstdint>

int main() {
    std::uint8_t x = 233;
    std::cout << static_cast<int>(x) << std::endl;  // Print numeric value
    std::cout << static_cast<void*>(&x) << std::endl;  // Print address properly
    return 0;
}