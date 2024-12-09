// main.cpp
#include "header.h"

namespace MyNamespace {
    void f(S* s) {
        std::cout << "S: " << s->a << ", " << s->b << std::endl;
    }
}

int main() {
    MyNamespace::S s{10, 'A'};
    MyNamespace::f(&s);

    MyClass<int> obj(42);
    obj.display();

    return 0;
}
