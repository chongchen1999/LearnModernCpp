// main.cpp
#include <iostream>
#include "myheader.h"

namespace {
    // File-local global variables
    int file_local_variable = 42;

    // File-local helper function
    void helper() {
        std::cout << "Helper function\n";
    }
}

namespace MyNamespace {
    void printPoint(const Point& p) {
        std::cout << "Point(" << p.x << ", " << p.y << ")\n";
    }
}

int main() {
    MyNamespace::Point p = {3, 4};
    MyNamespace::printPoint(p);

    helper();  // Calls the file-local helper function
    std::cout << "File-local variable: " << file_local_variable << '\n';
    std::cout << "Version: " << VERSION << '\n';
    return 0;
}