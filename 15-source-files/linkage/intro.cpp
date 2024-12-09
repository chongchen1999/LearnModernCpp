#include <iostream>

// External linkage examples
int x = 1;  // Definition with external linkage
extern int y;  // Declaration of an external variable

int f() { return x + 1; }  // Function with external linkage
extern int g();  // Declaration of an external function

// Internal linkage examples
static int internalVar = 42;  // Internal linkage
const char internalConst = 'a';  // Internal linkage by default

// Inline function in the same translation unit
inline int next(int i) { return i + 1; }  // Inline function

// Main function to demonstrate usage
int main() {
    // External linkage variables and functions
    x = 10;
    std::cout << "x: " << x << "\n";  // Uses global x
    std::cout << "y = " << y << "\n";
    std::cout << "f(): " << f() << "\n";

    // Internal linkage variable
    std::cout << "internalVar: " << internalVar << "\n";
    std::cout << "internalConst: " << internalConst << "\n";

    // Inline function
    std::cout << "next(5): " << next(5) << "\n";

    return 0;
}

// External definition
int y = 20;
// int g() { return y * 2; }
