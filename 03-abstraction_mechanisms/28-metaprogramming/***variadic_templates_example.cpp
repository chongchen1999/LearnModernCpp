// variadic_templates_example.cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>

// Utility function to check if a type is a C-style string
template<typename T>
constexpr bool Is_C_style_string() {
    return std::is_same_v<T, const char*> || std::is_same_v<T, char*>;
}

// Utility function to check if a type is std::string
template<typename T>
constexpr bool Is_string() {
    return std::is_same_v<T, std::string>;
}

// Base case for variadic printf
void printf(const char* s) {
    if (s == nullptr) return;
    while (*s) {
        if (*s == '%' && *++s != '%') // Invalid if more arguments are expected
            throw std::runtime_error("invalid format: missing arguments");
        std::cout << *s++;
    }
}

// Recursive case for variadic printf
template<typename T, typename... Args>
void printf(const char* s, T value, Args... args) {
    while (s && *s) {
        if (*s == '%' && *++s != '%') {
            std::cout << value;          // Print the first argument
            return printf(++s, args...); // Recursive call for remaining arguments
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf");
}

// Variadic template example function
template<typename... Types>
void example_variadic_function(Types... args) {
    std::cout << "Number of arguments: " << sizeof...(args) << "\n";
}

// Variadic template for argument forwarding
template<typename F, typename... T>
void call(F&& f, T&&... t) {
    f(std::forward<T>(t)...); // Perfect forwarding
}

// Variadic tuple implementation
template<typename Head, typename... Tail>
class tuple : private tuple<Tail...> {
    Head m_head;

public:
    tuple(Head head, Tail... tail)
        : m_head(head), tuple<Tail...>(tail...) {}

    Head head() const { return m_head; }
    tuple<Tail...>& tail() { return *this; }
};

// Base case for tuple (empty)
template<>
class tuple<> {};

// Example usage
int main() {
    // Type-safe printf
    printf("Hello, %! This is % and number %!\n", "world", "C++", 2023);

    // Variadic template function
    example_variadic_function(1, 2.5, "Hello");

    // Variadic template with perfect forwarding
    auto lambda = [](auto... args) {
        (std::cout << ... << args) << "\n";
    };
    call(lambda, 1, " variadic", ' ', 3.14);

    // Variadic tuple usage
    tuple<int, double, std::string> my_tuple(1, 2.5, "Hello");
    std::cout << "First element: " << my_tuple.head() << "\n";
    std::cout << "Second element: " << my_tuple.tail().head() << "\n";
    std::cout << "Third element: " << my_tuple.tail().tail().head() << "\n";

    return 0;
}
