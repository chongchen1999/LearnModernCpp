#include <limits>
#include <iostream>
#include <climits>
#include <cfloat>

void demo_numeric_limits() {
    int i = 123456;
    double d = 0.00001;

    // Example usage of numeric_limits
    if (i < std::numeric_limits<short>::min() || i > std::numeric_limits<short>::max()) {
        std::cout << "Value of i cannot fit into a short type.\n";
    }

    if (0 < d && d < std::numeric_limits<double>::epsilon()) {
        d = 0; // d is too small to be meaningful
    }

    if (std::numeric_limits<unsigned char>::digits == std::numeric_limits<char>::digits) {
        std::cout << "On this platform, chars are unsigned by default.\n";
    }

    // Displaying properties of float
    std::cout << "Float Min: " << std::numeric_limits<float>::min() << "\n";
    std::cout << "Float Max: " << std::numeric_limits<float>::max() << "\n";
    std::cout << "Float Epsilon: " << std::numeric_limits<float>::epsilon() << "\n";
}

void demo_limit_macros() {
    // Integer limits from <climits>
    std::cout << "CHAR_BIT: " << CHAR_BIT << "\n";
    std::cout << "INT_MIN: " << INT_MIN << "\n";
    std::cout << "LONG_MAX: " << LONG_MAX << "\n";

    // Floating-point limits from <cfloat>
    std::cout << "FLT_MIN: " << FLT_MIN << "\n";
    std::cout << "FLT_MAX: " << FLT_MAX << "\n";
    std::cout << "DBL_EPSILON: " << DBL_EPSILON << "\n";
}

int main() {
    std::cout << "Demonstrating numeric_limits:\n";
    demo_numeric_limits();
    std::cout << "\nDemonstrating limit macros:\n";
    demo_limit_macros();
    return 0;
}
