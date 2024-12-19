// header.h
#pragma once  // Ensures this file is included only once

#include <iostream>

namespace MyNamespace {
    struct Point {
        int x, y;
    };

    struct S {
        int a;
        char b;
    };

    void f(S*);
}

template <typename T>
class MyClass {
public:
    T value;
    MyClass(T v) : value(v) {}
    void display() {
        std::cout << value << std::endl;
    }
};
