#include <iostream>
#include <cmath>  // For sqrt, sin, cos, etc.

class complex {
    double re, im;
public:
    // Constructors
    constexpr complex(double r = 0, double i = 0) : re{r}, im{i} { }

    // Accessor functions
    constexpr double real() const { return re; }
    constexpr double imag() const { return im; }
    void real(double r) { re = r; }
    void imag(double i) { im = i; }

    // Operators
    constexpr complex& operator+=(complex a) {
        re += a.re; im += a.im; 
        return *this;
    }
    constexpr complex& operator+=(double a) {
        re += a; 
        return *this;
    }
    friend constexpr complex operator+(complex a, complex b) { return a += b; }
    friend constexpr complex operator+(complex a, double b) { return {a.re + b, a.im}; }
    friend constexpr complex operator+(double a, complex b) { return {a + b.re, b.im}; }

    // Unary operators
    friend complex operator-(complex a) { return {-a.re, -a.im}; }
    friend complex operator+(complex a) { return a; }  // Unary plus

    // Comparison operators
    friend bool operator==(complex a, complex b) {
        return a.real() == b.real() && a.imag() == b.imag();
    }
    friend bool operator!=(complex a, complex b) { return !(a == b); }

    // Input/Output
    friend std::ostream& operator<<(std::ostream& os, complex a) {
        return os << "{" << a.real() << ", " << a.imag() << "}";
    }
    friend std::istream& operator>>(std::istream& is, complex& a) {
        double r, i;
        is >> r >> i;
        a = complex{r, i};
        return is;
    }
};

// User-defined literal for imaginary numbers (not constexpr to support runtime calculations)
inline constexpr complex operator"" _i(long double d) {
    return {0, static_cast<double>(d)};
}

// Helper functions
inline complex polar(double rho, double theta) {
    return {rho * cos(theta), rho * sin(theta)};
}
inline complex conj(complex a) { return {a.real(), -a.imag()}; }
inline double abs(complex a) { return sqrt(a.real() * a.real() + a.imag() * a.imag()); }
inline double arg(complex a) { return atan2(a.imag(), a.real()); }
inline double norm(complex a) { return a.real() * a.real() + a.imag() * a.imag(); }

// Example usage
int main() {
    constexpr complex z1{1.2, 3.4};
    constexpr complex z2{5.6};  // Imaginary part defaults to 0
    constexpr complex z3 = complex{1.3} + complex{4.5_i};  // Explicit complex numbers
    std::cout << "z1 = " << z1 << "\n";
    std::cout << "z2 = " << z2 << "\n";
    std::cout << "z3 = " << z3 << "\n";

    complex a{1, 2};
    complex b{3, 4};
    complex c = a + b;
    complex d = 2 + a;  // mixed-mode addition

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = a + b = " << c << "\n";
    std::cout << "d = 2 + a = " << d << "\n";
    std::cout << "conj(a) = " << conj(a) << "\n";
    std::cout << "|a| = " << abs(a) << "\n";
    std::cout << "arg(a) = " << arg(a) << "\n";

    complex input;
    std::cout << "Enter a complex number (real and imaginary): ";
    std::cin >> input;
    std::cout << "You entered: " << input << "\n";

    return 0;
}
