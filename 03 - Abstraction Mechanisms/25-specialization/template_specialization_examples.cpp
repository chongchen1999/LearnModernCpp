#include <iostream>
#include <cstring>
#include <climits>

// 1. Complex Template Specialization
template<typename T>
class complex {
    T re, im;
public:
    complex(const T& re = T{}, const T& im = T{}) {} // General constructor
    complex(const complex&) {}                      // Copy constructor
    template<typename X>
    complex(const complex<X>&) {}                  // Conversion constructor
    complex& operator=(const complex&) { return *this; }
    complex<T>& operator=(const T&) { return *this; }
    complex<T>& operator+=(const T&) { return *this; }
    template<typename X>
    complex<T>& operator=(const complex<X>&) { return *this; }
    template<typename X>
    complex<T>& operator+=(const complex<X>&) { return *this; }
};

// Specialization for `float`
template<>
class complex<float> {
    float re;
public:
    complex<float>& operator=(float) { return *this; }
    complex<float>& operator+=(float) { return *this; }
    complex<float>& operator=(const complex<float>&) { return *this; }
};

// Specialization for `double`
template<>
class complex<double> {
    double re, im, real;
public:
    constexpr complex(double re = 0.0, double im = 0.0) {}
    constexpr complex(const complex<float>&) {}
    explicit constexpr complex(const complex<long double>&) {}
};

// 2. Matrix Template Specialization
template<typename T, int N>
class Matrix;

template<typename T>
class Matrix<T, 0> {
    T val;
};

template<typename T>
class Matrix<T, 1> {
    T* elem;
    int sz;
};

template<typename T>
class Matrix<T, 2> {
    T* elem;
    int dim1, dim2;
};

// 3. Function Template Specialization
template<typename T>
bool less(T a, T b) {
    return a < b;
}

template<>
bool less(const char* a, const char* b) {
    return strcmp(a, b) < 0;
}

// 4. Max Value Example
template<typename T>
T max_value();

template<> constexpr int max_value<int>() { return INT_MAX; }
template<> constexpr char max_value<char>() { return CHAR_MAX; }

template<typename Iter>
Iter my_algo(Iter p) {
    // Use max_value with Value_type<Iter>
    // Placeholder example since Value_type is undefined
    return p;
}

int main() {
    complex<int> c1;
    complex<float> c2;
    complex<double> c3;
    complex<long double> c4;

    std::cout << sizeof(complex<int>) << std::endl;
    std::cout << sizeof(complex<float>) << std::endl;
    std::cout << sizeof(complex<double>) << std::endl;
    std::cout << sizeof(complex<long double>) << std::endl;
    std::cout << sizeof(complex<long long>) << std::endl;

    return 0;
}