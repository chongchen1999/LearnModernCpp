#include <iostream>
#include <cmath>

// 1. Static Member Initialization
class Node {
public:
    static int node_count;  // Static member declaration
};

// Static member definition outside the class
int Node::node_count = 0;

// 2. Class with Static Members initialized inside the class
class Curious {
public:
    static const int c1 = 7;          // Valid: constant integer, initialized inside the class
    static int c2;               // Error: 'c2' is not const
    static inline int c4 = 17;            // Valid: 'c4' is initialized inside the class
    const int c3 = 13;                // Valid, but not static, should be an instance variable
    static const inline float c5 = 17.0;     // Error: float should be 'constexpr' instead of 'const'
};

// Definition of static member outside the class
// const int Curious::c1 = 7;  // This is necessary to allocate storage for c1
// const float Curious::c5 = 17.0;

// 3. Using `constexpr` for compile-time constants
class Fixed {
public:
    static constexpr int max = 10;  // 'constexpr' guarantees compile-time constant
private:
    int a[max];  // Use 'max' to define the size of the array
};

// 4. Using `enum` for symbolic constants
class X {
public:
    enum { c1 = 7, c2 = 11, c3 = 13, c4 = 17 };  // Symbolic constants defined with enum
};

int Curious::c2 = 17; 

int main() {
    // 1. Static member example
    Node::node_count = 5;
    std::cout << "Node count: " << Node::node_count << std::endl;

    // 2. Accessing the static constant member in Curious
    std::cout << "Curious c1: " << Curious::c1 << std::endl;
    // The following line would cause an error:
    std::cout << "Curious c2: " << Curious::c2 << std::endl;

    // 3. Using Fixed with constexpr
    Fixed f;
    std::cout << "Fixed max size: " << Fixed::max << std::endl;

    // 4. Using enum constants in X
    std::cout << "X c1: " << X::c1 << ", X c2: " << X::c2 << std::endl;

    return 0;
}
