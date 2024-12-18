#include <iostream>
#include <type_traits>

// Helper: Power function
constexpr int ipow(int base, int exp) {
    return (exp > 0) ? base * ipow(base, exp - 1) : 1;
}

// Helper: Process single ternary digit
template <char c>
constexpr int b3_helper() {
    static_assert(c >= '0' && c < '3', "Invalid ternary digit");
    return c - '0';
}

// Helper: Process multiple ternary digits
template <char c, char... rest>
constexpr int b3_helper() {
    static_assert(c >= '0' && c < '3', "Invalid ternary digit");
    return ipow(3, sizeof...(rest)) * (c - '0') + b3_helper<rest...>();
}

// Literal operator for base-3 numbers
template <char... chars>
constexpr int operator"" _b3() {
    return b3_helper<chars...>();
}

// Usage
int main() {
    constexpr int num = 102_b3; // Base-3 equivalent of 11 in decimal
    std::cout << "Base-3 literal: " << num << "\n";

    // Uncommenting this will result in a compile-time error
    // constexpr int invalid = 2014_b3; 
    return 0;
}
