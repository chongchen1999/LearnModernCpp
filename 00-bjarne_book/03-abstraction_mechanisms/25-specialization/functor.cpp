#include <iostream>
using namespace std;

class Functor {
private:
    int factor;

public:
    Functor(int f) : factor(f) {}

    // Overload the callable operator
    int operator()(int value) const {
        return value * factor;
    }
};

int main() {
    Functor f1(2);  // Functor instance with factor = 2
    Functor f2(3);  // Functor instance with factor = 3

    // Addresses of operator()
    auto func1 = &Functor::operator();
    auto func2 = &Functor::operator();

    cout << "Address of operator() for f1: " << func1 << endl;
    cout << "Address of operator() for f2: " << func2 << endl;

    // Invoke operator() on different instances
    cout << "f1(5): " << f1(5) << endl;  // Output: 10
    cout << "f2(5): " << f2(5) << endl;  // Output: 15

    return 0;
}
