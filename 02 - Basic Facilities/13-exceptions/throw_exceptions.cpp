#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <type_traits>

class MyError {
    // Custom error class
};

class NoCopy {
    NoCopy(const NoCopy&) = delete; // Prohibit copying
};

struct SimpleError { }; // Minimal error class

void h() {
    std::string s = "not";
    throw MyError{};
    std::string s2 = "at all"; // Never reached
}

void g() {
    std::string s = "excess";
    h();
}

void f() {
    std::string name = "Byron";
    try {
        g();
    } catch (MyError&) {
        std::cerr << "Caught MyError\n";
    }
}

void lightweightThrow() {
    throw SimpleError{};
}

void g_with_std(int n) {
    if (n)
        throw std::runtime_error{"I give up!"};
    else
        throw MyError{};
}

void f_with_std(int n) {
    try {
        g_with_std(n);
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

double compute(double x) noexcept {
    std::string s = "Example";
    std::vector<double> v(10); // May throw std::bad_alloc
    return x;
}

template<typename T>
void myFunction(T& x) noexcept(std::is_pod<T>::value) {
    // Safe for POD types
}

int main() {
    f();
    try {
        lightweightThrow();
    } catch (SimpleError&) {
        std::cerr << "Caught SimpleError\n";
    }

    f_with_std(1);
    return 0;
}
