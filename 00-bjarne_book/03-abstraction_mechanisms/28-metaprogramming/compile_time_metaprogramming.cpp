#include <type_traits>
#include <iostream>

// Conditional Selection
template<bool C, typename T, typename F>
struct conditional_ {
    using type = T;
};

template<typename T, typename F>
struct conditional_<false, T, F> {
    using type = F;
};

template<bool B, typename T, typename F>
using Conditional = typename conditional_<B, T, F>::type;

// Select for Multiple Types
template<int I, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void>
struct select_;

template<typename T1, typename T2, typename T3, typename T4>
struct select_<0, T1, T2, T3, T4> { using type = T1; };

template<typename T1, typename T2, typename T3, typename T4>
struct select_<1, T1, T2, T3, T4> { using type = T2; };

template<typename T1, typename T2, typename T3, typename T4>
struct select_<2, T1, T2, T3, T4> { using type = T3; };

template<typename T1, typename T2, typename T3, typename T4>
struct select_<3, T1, T2, T3, T4> { using type = T4; };

template<int I, typename T1, typename T2, typename T3, typename T4>
using Select = typename select_<I, T1, T2, T3, T4>::type;

// Factorial using Template Recursion
template<int N>
struct Fac {
    static const int value = N * Fac<N - 1>::value;
};

template<>
struct Fac<1> {
    static const int value = 1;
};

// Factorial using Constexpr Function
constexpr int fac(int n) {
    return (n < 2) ? 1 : n * fac(n - 1);
}

// Main Function for Demonstration
int main() {
    // Conditional example
    Conditional<true, int, double> a;  // int
    Conditional<false, int, double> b; // double

    // Select example
    Select<2, int, double, char, bool> c;  // char

    // Factorial
    constexpr int x = Fac<5>::value;  // 120
    constexpr int y = fac(5);         // 120

    std::cout << "Factorial using template: " << x << "\n";
    std::cout << "Factorial using constexpr: " << y << "\n";

    return 0;
}
