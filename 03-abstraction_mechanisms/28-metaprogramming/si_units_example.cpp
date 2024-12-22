// si_units_example.cpp

#include <iostream>
#include <string>

// Define Unit template for representing dimensions
template<int M, int K, int S>
struct Unit {
    static constexpr int m = M;
    static constexpr int kg = K;
    static constexpr int s = S;
};

// Common units
using M = Unit<1, 0, 0>;  // meters
using Kg = Unit<0, 1, 0>; // kilograms
using S = Unit<0, 0, 1>;  // seconds
using MpS = Unit<1, 0, -1>;  // meters per second
using MpS2 = Unit<1, 0, -2>; // meters per second squared

// Quantity template
template<typename U>
struct Quantity {
    double val;

    // Make the constructor constexpr
    constexpr explicit Quantity(double d) : val(d) {}

    // Default copy and assignment operators
    constexpr Quantity(const Quantity&) = default;
    constexpr Quantity& operator=(const Quantity&) = default;
};

// Unit addition and subtraction
template<typename U1, typename U2>
struct Uplus {
    using type = Unit<U1::m + U2::m, U1::kg + U2::kg, U1::s + U2::s>;
};

template<typename U1, typename U2>
struct Uminus {
    using type = Unit<U1::m - U2::m, U1::kg - U2::kg, U1::s - U2::s>;
};

template<typename U1, typename U2>
using Unit_plus = typename Uplus<U1, U2>::type;

template<typename U1, typename U2>
using Unit_minus = typename Uminus<U1, U2>::type;

// Arithmetic operators for Quantity
template<typename U>
constexpr Quantity<U> operator+(Quantity<U> x, Quantity<U> y) {
    return Quantity<U>{x.val + y.val};
}

template<typename U>
constexpr Quantity<U> operator-(Quantity<U> x, Quantity<U> y) {
    return Quantity<U>{x.val - y.val};
}

template<typename U1, typename U2>
constexpr Quantity<Unit_plus<U1, U2>> operator*(Quantity<U1> x, Quantity<U2> y) {
    return Quantity<Unit_plus<U1, U2>>{x.val * y.val};
}

template<typename U1, typename U2>
constexpr Quantity<Unit_minus<U1, U2>> operator/(Quantity<U1> x, Quantity<U2> y) {
    return Quantity<Unit_minus<U1, U2>>{x.val / y.val};
}

template<typename U>
constexpr Quantity<U> operator*(Quantity<U> x, double y) {
    return Quantity<U>{x.val * y};
}

template<typename U>
constexpr Quantity<U> operator*(double x, Quantity<U> y) {
    return Quantity<U>{x * y.val};
}

// User-defined literals
constexpr Quantity<M> operator"" _m(long double d) {
    return Quantity<M>{static_cast<double>(d)};
}

constexpr Quantity<S> operator"" _s(long double d) {
    return Quantity<S>{static_cast<double>(d)};
}

constexpr Quantity<Kg> operator"" _kg(long double d) {
    return Quantity<Kg>{static_cast<double>(d)};
}

// Output operator
template<typename U>
std::ostream& operator<<(std::ostream& os, Quantity<U> v) {
    return os << v.val << (U::m ? "m" : "") << (U::kg ? "kg" : "") << (U::s ? "s" : "");
}

int main() {
    constexpr auto distance = Quantity<M>{10.0}; // Explicit initialization
    constexpr auto time = Quantity<S>{20.0};    // Explicit initialization
    constexpr auto speed = distance / time;     // Division remains constexpr

    std::cout << "distance: " << distance << "\n";
    std::cout << "time: " << time << "\n";
    std::cout << "speed: " << speed << "\n";

    return 0;
}
