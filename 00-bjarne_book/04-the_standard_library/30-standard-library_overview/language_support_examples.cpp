// File: language_support_examples.cpp

#include <new>
#include <typeinfo>
#include <iterator>
#include <initializer_list>
#include <vector>
#include <iostream>

// Demonstrate new and delete
void demonstrate_new_delete() {
    int* p = new int(42);
    std::cout << "Value: " << *p << '\n';
    delete p;
}

// Demonstrate typeid and type_info
void demonstrate_typeinfo() {
    class Base {};
    class Derived : public Base {};

    Base* b = new Derived();
    std::cout << "Type: " << typeid(*b).name() << '\n';
    delete b;
}

// Demonstrate range-for loop with iterators
void demonstrate_range_for() {
    std::vector<int> v = {1, 2, 3, 4};
    for (int x : v) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

// Demonstrate initializer_list
void demonstrate_initializer_list() {
    auto display = [](std::initializer_list<int> lst) {
        for (auto x : lst) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    };

    display({10, 20, 30, 40});
}

int main() {
    demonstrate_new_delete();
    demonstrate_typeinfo();
    demonstrate_range_for();
    demonstrate_initializer_list();
    return 0;
}
