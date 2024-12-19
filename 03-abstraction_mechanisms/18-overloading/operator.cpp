#include <iostream>
using namespace std;

// Complex Number Class
class Complex {
    double real, imag;

public:
    // Constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Overload + operator (member function)
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overload * operator (non-member function)
    friend Complex operator*(const Complex& a, const Complex& b) {
        std::cout << "Overloaded * operator for non-member function\n";
        return Complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
    }

    Complex operator*(const Complex &a) {
        std::cout << "Overloaded * operator for Complex class\n";
        return Complex(
            this->real * a.real - this->imag * a.imag, 
            this->real * a.imag + this->imag * a.real
        );
    }
    
    // Overload == operator
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // Overload << (output) operator
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }

    // Overload >> (input) operator
    friend istream& operator>>(istream& is, Complex& c) {
        is >> c.real >> c.imag;
        return is;
    }
};

// Enumeration Example: Overload ++ for Days of Week
enum Day { Sun, Mon, Tue, Wed, Thu, Fri, Sat };

// Overload prefix ++ operator for Day
Day& operator++(Day& d) {
    d = (d == Sat) ? Sun : static_cast<Day>(d + 1);
    return d;
}

// Main Function to Demonstrate Operator Overloading
int main() {
    // Complex Number Example
    Complex a(1, 2), b(3, 4), c;

    cout << "Enter a complex number (real and imaginary parts): ";
    cin >> c;

    Complex sum = a + b;
    Complex product = a * b;

    cout << "Complex a: " << a << "\n";
    cout << "Complex b: " << b << "\n";
    cout << "Sum (a + b): " << sum << "\n";
    cout << "Product (a * b): " << product << "\n";
    cout << "Entered complex: " << c << "\n";

    // Compare Complex Numbers
    if (a == b) {
        cout << "a and b are equal.\n";
    } else {
        cout << "a and b are not equal.\n";
    }

    // Enumeration Example
    Day today = Tue;
    cout << "Today: " << today << "\n";

    ++today; // Increment day
    cout << "Tomorrow: " << today << "\n";

    return 0;
}
