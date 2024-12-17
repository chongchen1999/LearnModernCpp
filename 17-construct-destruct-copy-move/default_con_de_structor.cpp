#include <iostream>
#include <string>
#include <valarray>

class gslice {
    std::valarray<size_t> size;
    std::valarray<size_t> stride;
    std::valarray<size_t> d1;

public:
    gslice() = default;                          // Default constructor
    ~gslice() = default;                         // Destructor
    gslice(const gslice&) = default;             // Copy constructor
    gslice(gslice&&) = default;                  // Move constructor
    gslice& operator=(const gslice&) = default;  // Copy assignment
    gslice& operator=(gslice&&) = default;       // Move assignment
};

struct S {
    std::string a;
    int b;
};

S f(S arg) {
    S s0{};           // Default construction
    S s1{s0};         // Copy construction
    s1 = arg;         // Copy assignment
    return s1;        // Move construction
}

int main() {
    // Testing gslice
    gslice g1, g2;
    g1 = g2;  // Copy assignment works because of = default

    // Testing struct S
    S s1{"Hello", 42};
    S s2 = f(s1);  // Test default operations
    std::cout << "s2.a: " << s2.a << ", s2.b: " << s2.b << '\n';
    return 0;
}
