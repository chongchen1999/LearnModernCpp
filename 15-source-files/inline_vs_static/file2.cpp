#include <iostream>

// Static variable (new definition, unrelated to file1.cpp)
static int staticVar = 30;

// Inline variable (same variable as in file1.cpp)
inline int inlineVar = 50;

void printFile2() {
    std::cout << "Static variable in file2: " << &staticVar << ' ' << staticVar << "\n";
    std::cout << "Inline variable in file2: " << &inlineVar << ' ' << inlineVar << "\n";
}
