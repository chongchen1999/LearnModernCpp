#include <iostream>
#include <cstdint>

int main() {
    std::uint8_t x = 233;
     // Print numeric value
    std::cout << static_cast<int>(x) << std::endl;

    // Print address properly
    std::cout << static_cast<void *>(&x) << std::endl;
    return 0;
}
