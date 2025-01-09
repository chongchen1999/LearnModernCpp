#include <iostream>

// Example 1: Conditional Compilation
#define ARG_TWO // Uncomment this to enable ARG_TWO-related code

#ifdef ARG_TWO
    #define MESSAGE "ARG_TWO is defined"
#else
    #define MESSAGE "ARG_TWO is not defined"
#endif

// Example 2: Predefined Macros
void predefined_macros_example() {
    std::cout << "Current file: " << __FILE__ << "\n";
    std::cout << "Current line: " << __LINE__ << "\n";
    std::cout << "Compiled at: " << __DATE__ << " " << __TIME__ << "\n";

    // Example: Function name macro (__func__ is more standard in C++)
    std::cout << "Function name: " << __func__ << "\n";
}

// Example 3: Conditional Compilation within Function Declaration
int f(int a
#ifdef ARG_TWO
    , int b // This argument only exists if ARG_TWO is defined
#endif
) {
    return a
#ifdef ARG_TWO
           + b
#endif
        ;
}

// Example 4: Dangerous Macro Collisions
#define arg_two x // Problematic macro that can conflict with other identifiers

struct Call_info {
    int arg_one;
    int arg_two; // This will clash with the macro `arg_two` and cause unexpected behavior
};

// Example 5: Pragmas
// Note: #pragma directives are compiler-specific. Here we use a basic one.
#pragma message("This is a pragma message. It is compiler-specific and may vary by compiler.")

int main() {
    std::cout << "Message: " << MESSAGE << "\n";

    // Demonstrating predefined macros
    predefined_macros_example();

    // Demonstrating conditional compilation in a function
    int result = f(10
#ifdef ARG_TWO
                   , 20
#endif
    );
    std::cout << "Result of f: " << result << "\n";

    // Demonstrating macro collision issues
    Call_info info;
    info.arg_one = 5;
    info.arg_two = 10; // This line may cause issues due to the `#define arg_two x` macro

    std::cout << "Call_info.arg_one: " << info.arg_one << "\n";
    std::cout << "Call_info.arg_two: " << info.arg_two << " (may conflict due to macro)\n";

    return 0;
}
