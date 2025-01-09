#include <iostream>
#include <cmath>
#include <complex>
#include <stdexcept>

using namespace std;

// Custom narrow_cast function
template<class Target, class Source>
Target narrow_cast(Source v) {
    auto r = static_cast<Target>(v); // Convert to target type
    if (static_cast<Source>(r) != v) // Check for data loss
        throw runtime_error("narrow_cast failed");
    return r;
}

// Demonstration of implicit, explicit conversions, and casts
int main() {
    // Implicit Conversions
    double d = 1234567890; // Implicit integer to floating-point
    int i = d;             // Implicit floating-point to integer
    cout << "Implicit conversion: Double: " << d << ", Integer: " << i << endl;

    // Explicit Conversion with {} (type-safe)
    int j {static_cast<int>(7.9)}; // Explicit, avoids narrowing
    cout << "Explicit conversion with {}: " << j << endl;

    // Named Casts
    // Static Cast
    int staticCasted = static_cast<int>(7.9); // Truncates
    cout << "Static cast: " << staticCasted << endl;

    // Reinterpret Cast
    int x = 0xFF;
    int* ptr = reinterpret_cast<int*>(&x); // Interpret int as pointer
    cout << "Reinterpret cast: Pointer value: " << ptr << endl;

    // Dynamic Cast
    class Base { public: virtual ~Base() {} };
    class Derived : public Base {};
    Base* base = new Derived();
    Derived* derived = dynamic_cast<Derived*>(base);
    if (derived)
        cout << "Dynamic cast succeeded" << endl;
    else
        cout << "Dynamic cast failed" << endl;
    delete base;

    // Const Cast
    const int constValue = 10;
    int* modifiable = const_cast<int*>(&constValue);
    *modifiable = 42;
    cout << "Const cast modified value: " << *modifiable << endl;

    // C-Style Cast
    int cStyleCasted = (int)d; // Truncates
    cout << "C-style cast: " << cStyleCasted << endl;

    // Function-Style Cast
    int functionCasted = int(d);
    complex<double> z = complex<double>(d);
    cout << "Function-style cast: Integer: " << functionCasted << ", Complex: " << z << endl;

    // Custom narrow_cast
    try {
        char narrowChar = narrow_cast<char>(300); // Should throw error
        cout << "Narrow cast result: " << narrowChar << endl;
    } catch (const runtime_error& e) {
        cerr << "Narrow cast failed: " << e.what() << endl;
    }

    return 0;
}
