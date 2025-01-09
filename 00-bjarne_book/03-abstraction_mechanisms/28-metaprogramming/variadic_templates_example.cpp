#include <iostream>
#include <string>
#include <stdexcept>
#include <type_traits>

// Base case: Only the format string
void printf_(const char* s) {
    if (s == nullptr) return;
    while (*s) {
        if (*s == '%' && *++s != '%') // %% represents a literal %
            throw std::runtime_error("invalid format: missing arguments");
        std::cout << *s++;
    }
}

// Recursive case: Format string and additional arguments
template <typename T, typename... Args>
void printf_(const char* s, T value, Args... args) {
    while (s && *s) {
        if (*s == '%') {
            switch (*++s) {
                case '%': break; // Literal '%'
                case 's':
                    if (!std::is_same<T, const char*>::value &&
                        !std::is_same<T, std::string>::value)
                        throw std::runtime_error("Bad printf_() format");
                    break;
                case 'd':
                    if (!std::is_integral<T>::value)
                        throw std::runtime_error("Bad printf_() format");
                    break;
                case 'g':
                    if (!std::is_floating_point<T>::value)
                        throw std::runtime_error("Bad printf_() format");
                    break;
                default:
                    throw std::runtime_error("Unknown format specifier");
            }
            std::cout << value;
            return printf_(++s, args...); // Recursive call
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf_");
}

// Main function to demonstrate usage
int main() {
    try {
        printf_("The value of %s is %d\n", "x", 42);
        printf_("Hello, %s! The value of Pi is approximately %g.\n", "Alice", 3.14159);
        // Uncomment to see runtime errors:
        // printf_("The value of %s is %d\n", 42); // Format mismatch
        // printf_("Extra arguments test: %d\n", 1, 2); // Extra arguments
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
