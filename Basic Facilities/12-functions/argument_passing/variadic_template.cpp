#include <iostream>
#include <string>

namespace cpp17 {

template <typename ...Args>
void log(const std::string &message, const Args &...args) {
    std::cout << message << ": ";
    (std::cout << ... << args) << '\n'; // C++17 fold expression
}
    
} // namespace cplusplus1 

namespace cpp {
    template <typename T>
    void printSingle(const T &arg) {
        std::cout << std::boolalpha << arg; // Adds better boolean output
    }

    // Recursive variadic template
    template <typename T, typename ...Args>
    void logRecursive(const T &first, const Args &...rest) {
        printSingle(first); // Print the first argument
        if constexpr (sizeof...(rest) > 0) { // If there are more arguments
            std::cout << ", ";
            logRecursive(rest...); // Recursive call
        }
    }

    template <typename ...Args>
    void log(const std::string &message, Args ...args) {
        std::cout << message << ": ";
        if constexpr (sizeof...(args) > 0) { // If there are arguments
            logRecursive(args...); // Start recursive unpacking
        }
        std::cout << '\n';
    }
} // namespace cpp

void test_fold_expression() {
    cpp17::log("Info");                      // Message only
    cpp17::log("Error", 404);               // Message + one argument
    cpp17::log("Debug", 42, "details");     // Message + two arguments
    cpp17::log("Warning", "low memory", 75); // Message + multiple arguments
}

void test_recursion_expand() {
    cpp::log("Info");                      // Message only
    cpp::log("Error", 404);               // Message + one argument
    cpp::log("Debug", 42, "details");     // Message + two arguments
    cpp::log("Warning", "low memory", 75); // Message + multiple arguments
    cpp::log("Test", 42, "hello", 3.14, true);
}

// Example usage
int main() {
    test_fold_expression();

    return 0;
}
