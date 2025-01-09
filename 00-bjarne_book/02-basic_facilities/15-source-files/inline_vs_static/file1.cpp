#include <iostream>

// Static variable
static int staticVar = 10;

// Inline variable (C++17+)
inline int inlineVar = 20;

void printFile1() {
    std::cout << "Static variable in file1: " << &staticVar << ' ' << staticVar << "\n";
    std::cout << "Inline variable in file1: " << &inlineVar << ' ' << inlineVar << "\n";
}
