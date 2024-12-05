#include <iostream>
#include <string>
#include <cstdio>

#define NAME "rest of line" // Simple macro example
#define MAC(x, y) "argument1: " #x " argument2: " #y // Macro with arguments
#define MIN(a, b) (((a) < (b)) ? (a) : (b)) // A safer macro example
#define SQUARE(a) ((a) * (a)) // Dangerous macro example
#define INCR_xx(xx) ((xx)++) // Another dangerous macro example
#define NAME2(a, b) a##b // Token concatenation
#define printx(x) std::cout << #x " = " << x << '\n'; // Stringizing operator
#define err_print(...) fprintf(stderr, "error: %s %d\n", __VA_ARGS__) // Variadic macro

// #undef SQUARE // Un-defining the macro SQUARE for safety

// Include guard example for header files (for reference only)
#ifndef HEADER_FILE
#define HEADER_FILE
// Header content
#endif

int NAME2(hack, cah)() {
    return 42;
}


void demonstrate_macros() {
    // Simple macro
    std::cout << "Macro NAME expanded: " << NAME << "\n";

    // Macro with arguments
    std::cout << "Macro MAC expanded: " << MAC(foo, bar) << "\n";

    // Safer macro with parentheses
    int x = 1, y = 10, z = MIN(x++, y++);
    std::cout << "Using MIN macro: x = " << x << ", y = " << y << ", z = " << z << "\n";

    // Dangerous macros
    x = 2;
    y = SQUARE(x + 1); // x + 1 * x + 1 instead of (x + 1) * (x + 1)
    std::cout << "Dangerous macro SQUARE result: y = " << y << "\n";

    int global_xx = 0; // Global variable
    std::cout << "Global variable global_xx before: " << global_xx << "\n";
    INCR_xx(global_xx); // Increment global variable
    std::cout << "Global variable global_xx after: " << global_xx << "\n";

    // Stringizing and token concatenation
    int hackcah_val = NAME2(hack, cah)();
    std::cout << "Function name created by NAME2: hackcah = " << hackcah_val << "\n";

    int a = 7;
    std::string str = "asdf";
    printx(a);
    printx(str);

    // Variadic macro
    err_print("The answer", 54);
}

int main() {
    demonstrate_macros();
    return 0;
}
