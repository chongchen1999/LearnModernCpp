#include <concepts>
#include <iostream>

// Declare f before the concept
void f(int x);

// Define a concept to check if f(T) is callable
template <typename T>
concept CallableWithF = requires(T t) {
    f(t); // Check if f(t) is a valid expression
};

// Custom function that uses the concept
template <CallableWithF T>
void use_f(const T& t) {
    f(t);
}

// Implementation of f
void f(int x) {
    std::cout << "f(" << x << ")\n";
}

// Example usage
void example_has_f() {
    static_assert(CallableWithF<int>, "int should have f()");
    use_f(10);
}

int main() {
    example_has_f();
    return 0;
}
