// templates.cpp
#include <iostream>
#include <string>

template<typename T>
struct X {
    int m1 = 7;             // Non-static member
    T m2;                   // Non-static member of type T
    static const int m3; // Const static data member
    static int m4;          // Static member

    X(const T& x) : m2{x} {}

    void f1() { /* in-class definition */ }
    void f2();
};

template<typename T> int X<T>::m4 = 99;
template<typename T> const int X<T>::m3 = 42;

template<typename T>
void X<T>::f2() { /* out-of-class definition */ }

// Type alias example
template<typename T>
class Vector_ {
public:
    using value_type = T;
    using iterator = T*;
};

// Static members example
template<typename T>
struct Y {
    static constexpr int m1 = 7;
    static int m2;

    static void f1() { /* ... */ }
    static void f2();
};

template<typename T>
int Y<T>::m2 = 88;

template<typename T>
void Y<T>::f2() { /* ... */ }

// Member type example
template<typename T>
struct Z {
    enum E1 { a, b };
    struct Inner;
};

template<typename T>
struct Z<T>::Inner {
    T value;
};

// Member template example
template<typename Scalar>
class Complex {
    Scalar re, im;

public:
    Complex() : re{}, im{} {}
    template<typename T>
    Complex(const T& real, const T& imag = 0) : re(real), im(imag) {}
};

template<typename T> class Matrix;
template<typename T> class Vector;

template<typename T> Vector<T> operator*(const Matrix<T>&, const Vector<T>&);

template<typename T> class Vector {
    T v[4];
public:
    friend Vector operator*<>(const Matrix<T>&, const Vector&);
};

template<typename T> Vector<T> operator*(const Matrix<T>&, const Vector<T>&);

template<typename T> class Matrix {
    T m[4][4];
public:
    friend Vector<T> operator*<>(const Matrix&, const Vector<T>&);
};

template<typename T>
Vector<T> operator*(const Matrix<T>& mat, const Vector<T>& vec) {
    Vector<T> result;
    // Perform multiplication logic
    return result;
}

int main() {
    X<int> xi(10);
    X<int> xj(20);
    X<float> x2(5.5);

    std::cout << static_cast<const void*>(&X<int>::m4) << std::endl;
    std::cout << static_cast<const void*>(&X<float>::m4) << std::endl;

    std::cout << static_cast<const void*>(&xi.m4) << std::endl;
    std::cout << static_cast<const void*>(&xj.m4) << std::endl;

    xi.f1();
    xi.f2();

    Vector<int> v;
    Y<double>::f1();
    return 0;
}
