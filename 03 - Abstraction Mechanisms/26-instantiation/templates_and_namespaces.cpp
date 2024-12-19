#include <iostream>
#include <vector>
#include <algorithm>

namespace multiple_instantiation_points {

// Fixed: Proper declaration and definitions to avoid binding issues
void f(double) {} // Adjusting f to handle double explicitly
namespace N {
    class X { };
    char g(X, int) { return 'i'; } // Returns a character
}

namespace N { // Ensure consistent visibility of g functions
    double g(X, double) { return 'd'; } // Now properly returns a character
}

template<typename T>
char ff(T t, double d) {
    f(d); // Now binds to the correct version of f
    return g(t, static_cast<int>(d)); // Resolves to the correct g
}

void example() {
    auto x1 = ff(N::X{}, 1.1);  // Now binds to N::g(X, int)
    auto x2 = ff(N::X{}, 2.2);  // Resolves to the consistent N::g(X, int) 
    std::cout << "x1: " << x1 << ", x2: " << x2 << '\n';
}

}  // namespace multiple_instantiation_points

namespace templates_and_namespaces {

namespace N {
    class A { };
    char f(A) { return 'A'; } // Found via argument's namespace
}
char f(int) { return 'I'; }    // Found in global scope

template<typename T>
char g(T t) {
    return f(t);  // Resolution depends on T
}

void example() {
    char c1 = g(N::A()); // Calls N::f, returns 'A'
    char c2 = g(2);      // Calls global f(int), returns 'I'
    std::cout << "c1: " << c1 << ", c2: " << c2 << '\n';
}

}  // namespace templates_and_namespaces

namespace adl_example {

namespace User {
    class Customer { };
    using Index = std::vector<Customer*>;

    void copy(const Index& src, Index& dest, int flag) { 
        // Custom copy logic here
        dest = src; 
        if (flag) {
            std::reverse(dest.begin(), dest.end());
        }
    }

    void algo(Index& x, Index& y) {
        User::copy(x, y, false);  // Explicit namespace avoids ADL issues
        std::swap(*x[0], *x[1]);  // Explicit std::swap avoids ambiguity
    }
}

}  // namespace adl_example

namespace base_class_names {

struct B {
    using Type = int;
    void g(char t) {
        std::cout << "B::g called with " << t << '\n';
    }
    void g2(char t) {
        std::cout << "B::g2 called with " << t << '\n';
    }
};

template<typename T>
class X : public T {
public:
    typename T::Type m; // OK
    void f() {
        this->g(2); // Calls T::g
        this->g2(2);      // Calls T::g2 explicitly
    }
};

void example() {
    struct Derived : B {};
    X<Derived> x;
    x.f();
}

}  // namespace base_class_names

int main() {
    using namespace multiple_instantiation_points;
    using namespace templates_and_namespaces;
    using namespace adl_example;
    using namespace base_class_names;

    // Call examples
    multiple_instantiation_points::example();
    templates_and_namespaces::example();
    base_class_names::example();

    return 0;
}
