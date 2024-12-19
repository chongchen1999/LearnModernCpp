#include <iostream>
#include <cmath>  // For math functions like sqrt()

class complex {
    double re, im;  // Real and imaginary parts
public:
    // Constructors
    complex(double r = 0, double i = 0) : re{r}, im{i} {}  // Default and parameterized constructor

    // Access functions
    double real() const { return re; }
    double imag() const { return im; }

    // Operator += for complex and double
    complex& operator+=(complex a) {
        re += a.re;
        im += a.im;
        return *this;
    }

    complex& operator+=(double a) {
        re += a;
        return *this;
    }

    complex& operator*(double a) {
        re *= a;
        im *= a;
        return *this;
    }

    complex& operator*(complex a) {
        double temp = re * a.re - im * a.im;
        im = re * a.im + im * a.re;
        re = temp;
        return *this;
    }

    // Overloaded << operator for printing
    friend std::ostream& operator<<(std::ostream& os, const complex& c) {
        os << "{" << c.re << ", " << c.im << "}";
        return os;
    }
};

// Non-member operator+ for complex and complex
complex operator+(complex a, complex b) {
    return a += b;  // Uses += operator
}

// Non-member operator+ for complex and double
complex operator+(complex a, double b) {
    return {a.real() + b, a.imag()};
}

// Non-member operator+ for double and complex
complex operator+(double a, complex b) {
    return {a + b.real(), b.imag()};
}

// Equality operator
bool operator==(complex a, complex b) {
    return a.real() == b.real() && a.imag() == b.imag();
}

// Testing the complex class
int main() {
    complex a{1, 2};     // a = {1, 2}
    complex b{3};        // b = {3, 0}
    complex c = a + 2.3; // {1+2.3, 2}
    complex d = 2 + b;   // {2+3, 0}

    b = c * 2 * c;  // You would need to define operator* for this.

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";
    std::cout << "c: " << c << "\n";
    std::cout << "d: " << d << "\n";

    // Test equality
    if (a == complex(1, 2)) {
        std::cout << "a equals {1, 2}\n";
    }

    // Mixed-mode arithmetic
    complex x{1, 2};
    complex y{3, 4};
    auto r1 = x + y;
    auto r2 = x + 2;
    auto r3 = 2 + x;

    std::cout << "r1: " << r1 << "\n";
    std::cout << "r2: " << r2 << "\n";
    std::cout << "r3: " << r3 << "\n";

    return 0;
}
