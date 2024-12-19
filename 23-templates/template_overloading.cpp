#include <iostream>
#include <vector>
#include <complex>

template<typename T>
T sqrt(T x) {
    return x * x; // Simplified implementation
}

template<typename T>
std::complex<T> sqrt(std::complex<T> x) {
    return std::complex<T>(x.real(), x.imag()); // Simplified
}

double sqrt(double x) {
    return x * x; // Regular function
}

template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

template<typename Iter>
typename Iter::value_type mean(Iter first, Iter last) {
    return *first; // Simplified
}

template<typename T>
T mean(T* first, T* last) {
    return *first; // Simplified
}

template<typename T>
class B {};

template<typename T>
class D : public B<T> {};

template<typename T>
void f(B<T>*) {
    std::cout << "Called f with B<T>*\n";
}

struct Index {
    operator int() { return 0; } // Simplified
};

template<typename T, typename U>
void get_nth(std::vector<T>& v, U n) {
}

void example_usage() {
    // sqrt examples
    std::complex<double> z(2, 3);
    sqrt(2);
    sqrt(2.0);
    // sqrt(z);

    // max examples
    max(1, 2);
    max('a', 'b');
    max(2.7, 4.9);

    // mean examples
    std::vector<int> v = {1, 2, 3};
    int arr[] = {1, 2, 3};
    mean(v.begin(), v.end());
    mean(arr, arr + 3);

    // f and inheritance examples
    B<int> b;
    D<int> d;
    f(&b);
    f(&d);

    // get_nth examples
    Index i;
    short s = 2;
    get_nth<int>(v, s);
    get_nth<int>(v, i);
}

int main() {
    example_usage();
    return 0;
}
