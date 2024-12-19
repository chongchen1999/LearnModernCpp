#include <iostream>
#include <vector>
#include <numeric>
#include <memory>

// Alias definitions
template<typename T, typename Allocator = std::allocator<T>> 
using vector = std::vector<T, Allocator>;

using Cvec = vector<char>;  // Alias for vector<char, std::allocator<char>>

template<typename T>
using Vec = vector<T, std::allocator<T>>;  // Example: Custom allocator alias

// Example: Using template specializations
template<int N>
struct int_exact_traits {
    using type = int;
};

template<>
struct int_exact_traits<8> {
    using type = char;
};

template<>
struct int_exact_traits<16> {
    using type = short;
};

template<int N>
using int_exact = typename int_exact_traits<N>::type;  // Alias for convenience

// Encapsulation of templates
double accum(const std::vector<double>& v) {
    return std::accumulate(v.begin(), v.end(), 0.0);
}

int main() {
    // Example usage of aliases
    Cvec vc = {'a', 'b', 'c'};
    for (char c : vc) {
        std::cout << c << " ";
    }
    std::cout << "\n";

    Vec<int> fib = {0, 1, 1, 2, 3, 5, 8, 13};
    for (int num : fib) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    int_exact<8> a = 'z';
    std::cout << "int_exact<8>: " << a << "\n";

    // Using encapsulated accumulate
    std::vector<double> numbers = {1.1, 2.2, 3.3};
    std::cout << "Sum: " << accum(numbers) << "\n";

    return 0;
}
