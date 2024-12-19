#include <iostream>
#include <cstdio>

// Demonstrating function overloading with different parameter types
void print(int value) {
    std::cout << "Printing integer: " << value << std::endl;
}

void print(double value) {
    std::cout << "Printing double: " << value << std::endl;
}

void print(const char* value) {
    std::cout << "Printing string: " << value << std::endl;
}

void print(char value) {
    std::cout << "Printing character: " << value << std::endl;
}

int main() {
    // Demonstrating overload resolution
    print(42);        // Calls print(int)
    print(3.14);      // Calls print(double)
    print("Hello");   // Calls print(const char*)
    print('A');       // Calls print(char)

    // Demonstrating type promotions and conversions
    short s = 100;
    print(s);         // Will use integral promotion to int

    // Demonstrating the complexity of overload resolution
    int x = 10;
    print(x);         // Exact match: print(int)

    // Showing how overloading helps avoid verbose naming
    return 0;
}