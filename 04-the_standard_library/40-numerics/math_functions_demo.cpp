#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstdlib>
#include <limits>

void test_math_functions() {
    errno = 0; // Clear old error state
    sqrt(-1); // Invalid input
    if (errno == EDOM)
        std::cerr << "sqrt() not defined for negative argument\n";

    errno = 0; // Clear error state
    pow(std::numeric_limits<double>::max(), 2); // Too large
    if (errno == ERANGE)
        std::cerr << "result of pow() too large to represent as a double\n";
}

void test_cstdlib_functions() {
    int n = -10, d = 3;
    auto res = div(n, d);
    std::cout << "Quotient: " << res.quot << ", Remainder: " << res.rem << '\n';
}

int main() {
    test_math_functions();
    test_cstdlib_functions();
    return 0;
}
