#include <iostream>
#include <string>
using namespace std;

// Define Unit template
template<int M, int K, int S>
struct Unit {
    enum { m = M, kg = K, s = S };
};

// Common Units
using M = Unit<1, 0, 0>;  // Meters
using Kg = Unit<0, 1, 0>; // Kilograms
using S = Unit<0, 0, 1>;  // Seconds
using MpS = Unit<1, 0, -1>;  // Meters per second (m/s)
using MpS2 = Unit<1, 0, -2>; // Meters per square second (m/s^2)

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

// Define Quantity
template<typename U>
struct Quantity {
    double val;
    explicit Quantity(double d) : val(d) {}
};

// Operators for Quantity
template<typename U>
Quantity<U> operator+(Quantity<U> x, Quantity<U> y) {
    return Quantity<U>{x.val + y.val};
}
template<typename U>
Quantity<U> operator-(Quantity<U> x, Quantity<U> y) {
    return Quantity<U>{x.val - y.val};
}
template<typename U1, typename U2>
Quantity<Unit_plus<U1, U2>> operator*(Quantity<U1> x, Quantity<U2> y) {
    return Quantity<Unit_plus<U1, U2>>{x.val * y.val};
}
template<typename U1, typename U2>
Quantity<Unit_minus<U1, U2>> operator/(Quantity<U1> x, Quantity<U2> y) {
    return Quantity<Unit_minus<U1, U2>>{x.val / y.val};
}
template<typename U>
Quantity<U> operator*(Quantity<U> x, double y) {
    return Quantity<U>{x.val * y};
}
template<typename U>
Quantity<U> operator*(double x, Quantity<U> y) {
    return Quantity<U>{x * y.val};
}

// User-defined literals
constexpr Quantity<M> operator"" _m(long double d) { return Quantity<M>{static_cast<double>(d)}; }
constexpr Quantity<S> operator"" _s(long double d) { return Quantity<S>{static_cast<double>(d)}; }

// Helper function for output
string suffix(int u, const char* x) {
    string suf;
    if (u) {
        suf += x;
        if (u > 1) suf += '0' + u;
        if (u < 0) {
            suf += '-';
            suf += '0' - u;
        }
    }
    return suf;
}

// Output operator
template<typename U>
ostream& operator<<(ostream& os, Quantity<U> v) {
    return os << v.val << suffix(U::m, "m") << suffix(U::kg, "kg") << suffix(U::s, "s");
}

// Main function
int main() {
    auto distance = 10.0_m; // 10 meters
    auto time = 20.0_s;     // 20 seconds
    auto speed = distance / time; // 0.5 m/s
    cout << "Speed: " << speed << endl;

    return 0;
}
