#pragma once  // Prevents multiple inclusions

namespace MyNamespace {
    struct Point {
        int x, y;
    };

    constexpr float pi = 3.14159;
    void printPoint(const Point& p);
}

#define VERSION 1.0