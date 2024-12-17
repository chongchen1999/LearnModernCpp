#include <iostream>

// Complex number class
class complex {
    double re, im; // Real and imaginary parts

public:
    // Constructor
    complex(double r, double i) : re{r}, im{i} { }

    // Overloaded + operator
    complex operator+(complex c) {
        return complex{re + c.re, im + c.im};
    }

    complex operator+=(complex c) {
        re += c.re;
        im += c.im;
        return *this;
    }

    // Overloaded * operator
    complex operator*(complex c) {
        return complex{re * c.re - im * c.im, re * c.im + im * c.re};
    }

    // Function to print complex number
    void print() const {
        std::cout << "(" << re << ", " << im << ")\n";
    }
};

void f() {
    complex a = complex{1, 3.1};  // Complex number 1 + 3.1i
    complex b{1.2, 2};            // Complex number 1.2 + 2i
    complex c{b};                 // Copy constructor

    a = b + c;                    // Uses operator+ to add b and c
    b = b + c * a;                // Uses operator* first (precedence), then operator+
    c = a * b + complex(1, 2);    // Combines operator* and operator+ with correct precedence

    a.print();
    b.print();
    c.print();
}

void g(complex a, complex b) {
    a = {1, 2};           // OK: {} is used on the right-hand side of assignment
    a += {1, 2};          // OK: {} is on the right-hand side of an assignment operator
    b = a + complex{1, 2}; // OK: Wrap {} inside an explicit complex object

    g(a, {1, 2});         // OK: {} used as a function argument initializer
}

int main() {
    f();
    return 0;
}
