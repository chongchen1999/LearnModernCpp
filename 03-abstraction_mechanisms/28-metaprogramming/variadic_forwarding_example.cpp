// filename: variadic_forwarding_example.cpp

#include <iostream>
#include <string>
#include <utility>

template<typename F, typename ... T>
void call(F&& f, T&&... t) {
    f(std::forward<T>(t)...);
}

// Example functions
void g0() {
    std::cout << "g0()\n";
}

template<typename T>
void g1(const T& t) {
    std::cout << "g1(): " << t << '\n';
}

void g1d(double t) {
    std::cout << "g1d(): " << t << '\n';
}

template<typename T, typename T2>
void g2(const T& t, T2&& t2) {
    std::cout << "g2(): " << t << ' ' << t2 << '\n';
}

// Test function
void test() {
    call(g0);
    call(g1<int>, 1);
    call(g1<const char*>, "hello");
    call(g1<double>, 1.2);
    call(g1d, 1.2);
    
    call(g2<double, std::string>, 1, "world!");
    int i = 99;
    const char* p = "Trying";
    call(g2<double, std::string>, i, p);

    // Test with lambdas
    call([]() { std::cout << "l1()\n"; });
    call([](int i) { std::cout << "l0(): " << i << "\n"; }, 17);
    call([i]() { std::cout << "l1(): " << i << "\n"; });
}

// Main function
int main() {
    test();
    return 0;
}
