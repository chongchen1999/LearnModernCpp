#include <iostream>

// First declaration of namespace A
namespace A {
    int f() {
        return 1;
    }
}

// Second declaration of namespace A
namespace A {
    int g() {
        return 2;
    }
}

// Reorganizing older code into namespaces
namespace Mine {
    void mf() {
        std::cout << "Mine::mf()\n";
    }
}

void yf() {  // Not in a namespace
    std::cout << "Global yf()\n";
}

namespace Mine {
    int mg() {
        return 42;
    }
}

int main() {
    // Using namespace A
    std::cout << "A::f(): " << A::f() << "\n";
    std::cout << "A::g(): " << A::g() << "\n";

    // Using reorganized code
    Mine::mf();
    yf();
    std::cout << "Mine::mg(): " << Mine::mg() << "\n";

    return 0;
}
