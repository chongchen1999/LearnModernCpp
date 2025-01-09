#include <type_traits>
#include <utility>
#include <iostream>

// Forward declare f before the has_f trait
void f(int x);

// Improved SFINAE detection
namespace detail {
    template <typename T>
    auto has_f_impl(int) -> decltype(f(std::declval<T>()), std::true_type{});

    template <typename T>
    std::false_type has_f_impl(...);
}

template <typename T>
struct has_f : decltype(detail::has_f_impl<T>(0)) {};

// Custom function that uses has_f
template <typename T>
typename std::enable_if<has_f<T>::value>::type use_f(const T& t) {
    f(t);
}

// Implementation of f
void f(int x) {
    std::cout << "f(" << x << ")\n";
}

// Example usage
void example_has_f() {
    static_assert(has_f<int>::value, "int should have f()");
    use_f(10);
}

int main() {
    example_has_f();
    return 0;
}   