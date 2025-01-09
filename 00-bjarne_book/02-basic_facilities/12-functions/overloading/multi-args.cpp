#include <iostream>
#include <complex>
#include <cmath>

// Multiple overloaded pow functions
int pow(int base, int exponent) {
    std::cout << "Calling pow(int, int)" << std::endl;
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

// double pow(double base, double exponent) {
//     std::cout << "Calling pow(double, double)" << std::endl;
//     return std::pow(base, exponent);
// }

std::complex<double> pow(double base, std::complex<double> exponent) {
    std::cout << "Calling pow(double, complex)" << std::endl;
    return std::pow(base, exponent);
}

std::complex<double> pow(std::complex<double> base, int exponent) {
    std::cout << "Calling pow(complex, int)" << std::endl;
    return std::pow(base, exponent);
}

std::complex<double> pow(std::complex<double> base, std::complex<double> exponent) {
    std::cout << "Calling pow(complex, complex)" << std::endl;
    return std::pow(base, exponent);
}

// Manual overload resolution demonstration
void f1(char c) {
    std::cout << "f1(char) called" << std::endl;
}

void f1(long l) {
    std::cout << "f1(long) called" << std::endl;
}

// Adding an overload to resolve ambiguity
inline void f1(int n) { 
    std::cout << "f1(int) resolving ambiguity" << std::endl;
    f1(static_cast<long>(n)); 
}

void f2(char*) {
    std::cout << "f2(char*) called" << std::endl;
}

void f2(int*) {
    std::cout << "f2(int*) called" << std::endl;
}

int main() {
    // Demonstrating multiple argument overload resolution
    std::complex<double> z(1.0, 2.0);

    int i = pow(static_cast<int>(2), static_cast<int>(2));                     // Uses pow(int, int)
    double d = pow(2.0, 2.0);              // Uses pow(double, double)
    std::complex<double> z2 = pow(static_cast<double>(2), z);   // Uses pow(double, complex)
    std::complex<double> z3 = pow(z, static_cast<int>(2));   // Uses pow(complex, int)
    std::complex<double> z4 = pow(z, z);   // Uses pow(complex, complex)

    // Demonstrating manual overload resolution
    int x = 10;
    f1(x);  // Now resolves to f1(int), which then calls f1(long)

    // Demonstrating explicit type conversion
    f2(static_cast<int*>(0));  // Explicitly resolves to f2(int*)

    return 0;
}