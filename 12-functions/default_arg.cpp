#include <iostream>
using namespace std;

class Complex {
    double re, im;
public:
    Complex(double r = 0.0, double i = 0.0) : re{r}, im{i} {}

    void print() const {
        cout << "Complex: " << re << " + " << im << "i" << endl;
    }
};

int main() {
    Complex c1;          // Default: 0.0 + 0.0i
    Complex c2(3.5);     // Default: 3.5 + 0.0i
    Complex c3(2.5, 4.5); // 2.5 + 4.5i

    c1.print();
    c2.print();
    c3.print();

    return 0;
}
