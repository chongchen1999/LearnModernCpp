#include <iostream>

int main() {
    try {
        throw std::runtime_error("Error occurred");
    } catch (...) { // Catch any exception
        std::cout << "Caught an exception\n";
    }
    return 0;
}
