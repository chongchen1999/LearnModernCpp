#include <type_traits>
#include <iostream>

// Function that only accepts integral types
template <typename T>
requires std::is_integral_v<T>
void print(T value) {
    std::cout << "Integral value: " << value << std::endl;
}

int main() {
    print(42);       // OK
    // print(3.14);  // Compilation error: Constraint not satisfied
}
