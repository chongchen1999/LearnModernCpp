#include <iostream>
#include <type_traits> // for std::underlying_type

// Define plain enums
enum Traffic_light { red, yellow, green }; // Enum without an underlying type
enum class Warning { green, yellow, orange, red }; // Conflicts with Traffic_light!

// Enum with specified underlying type
enum Flag : unsigned char { x = 1, y = 2, z = 4, e = 8 };

// Unnamed enum for constants
enum { arrow_up = 1, arrow_down, arrow_sideways };

void check_enum_behaviors() {
    // Scope pollution: plain enums export their names
    int a = green;               // OK: implicitly converts to int
    int b = static_cast<int>(Warning::green);      // OK: explicitly refers to Warning::green
    // int c = Traffic_light::green; // Error: Traffic_light::green not implicitly convertible to Warning::green

    std::cout << "a = " << a << ", b = " << b << '\n';

    // Implicit conversions and range issues
    Flag f1 = static_cast<Flag>(z | e); // OK: Bitwise operation, converts to underlying type
    std::cout << "Flag f1: " << static_cast<int>(f1) << '\n';

    Flag f2 = static_cast<Flag>(99); // Undefined behavior! Out of range
    std::cout << "Flag f2 (undefined): " << static_cast<int>(f2) << '\n';

    // Unnamed enums
    int move = arrow_up; // arrow_up behaves like an integer constant
    std::cout << "Move: " << move << '\n';

    // Size of enums depends on the range of their values
    std::cout << "Size of Traffic_light: " << sizeof(Traffic_light) << '\n';
    std::cout << "Size of Flag: " << sizeof(Flag) << '\n';

    // Example with an integer conversion
    int warningValue = 3;
    Warning warningLevel = static_cast<Warning>(warningValue); // Explicit conversion
    std::cout << "Warning level (explicit conversion): " << static_cast<int>(warningLevel) << '\n';
}

void check_scope_pollution(Traffic_light light) {
    // Demonstrating name conflicts
    if (light == red) { // Ambiguity with Warning::red, but compiler prefers Traffic_light::red
        std::cout << "Traffic_light is red!\n";
    }

    if (light == static_cast<int>(Warning::red)) { // Explicit disambiguation
        std::cout << "Warning level is red, not Traffic_light.\n";
    }
}

int main() {
    std::cout << "Plain Enum Demonstrations:\n";
    check_enum_behaviors();

    std::cout << "\nScope Pollution Demonstrations:\n";
    check_scope_pollution(Traffic_light::red);

    return 0;
}
