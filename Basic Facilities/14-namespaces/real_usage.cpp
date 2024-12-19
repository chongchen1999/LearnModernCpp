#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

// 1. Convenience vs. Safety
namespace X {
    int i, j, k;
}

int k; // Global `k`

void f1() {
    int i = 0;
    using namespace X;

    i++;
    j++;
    X::k++;
    ::k++;
}

void f2() {
    int i = 0;
    using X::j;
    using X::k;
}

// 2. Namespace Aliases
namespace American_Telephone_and_Telegraph {
    class String {};
}
namespace ATT = American_Telephone_and_Telegraph;
ATT::String s1;

// 3. Namespace Composition
namespace His_string {
    class String {};
}

namespace Her_vector {
    template <typename T>
    class Vector {};
}

namespace My_lib {
    using namespace His_string;
    using namespace Her_vector;

    void my_fct(String&);
}

// 4. Composition and Selection
namespace His_lib {
    class String {};
    template <typename T>
    class Vector {};
}

namespace Her_lib {
    template <typename T>
    class Vector {};
    class String {};
}

namespace My_lib {
    using His_lib::String;
    using Her_lib::Vector;
    template <typename T>
    class List {};
}

// 5. Namespaces and Overloading
namespace A {
    void f(int) {}
}

namespace B {
    void f(char) {}
}

// 6. Versioning
namespace Popular {
    inline namespace V3_2 {
        double f(double x) { return x; }
    }
    namespace V3_0 {
        double f(double x) { return x * 2; }
    }
}

// 7. Nested Namespaces
namespace X {
    namespace Y {
        void f() {}
    }
}

// 8. Unnamed Namespaces
namespace {
    int a;
    void f() {}
}

// Main function to demonstrate usage
int main() {
    using namespace Popular;
    cout << f(1.0) << endl; // Calls `Popular::V3_2::f`

    return 0;
}
