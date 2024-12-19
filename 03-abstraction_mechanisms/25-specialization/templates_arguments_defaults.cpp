#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <stdexcept>

// Template as a template argument example
template<typename T, template<typename> class C>
class Xrefd {
    C<T> mems;
    C<T*> refs;
};

// Custom vector alias
template<typename T>
using My_vec = std::vector<T>;

// Custom container example
template<typename T>
class My_container {
    // Custom implementation
};

// Xrefd usage examples
Xrefd<int, My_vec> x1;
Xrefd<int, My_container> x2;

// Default template argument example
template<typename Key, typename Value, typename Compare = std::less<Key>>
class My_map {
public:
    explicit My_map(const Compare& comp = {}) {
        // Implementation
    }
};

// Function template with default template arguments
template<typename Target = std::string, typename Source = std::string>
Target to(Source arg) {
    std::stringstream interpreter;
    Target result;
    if (!(interpreter << arg) || !(interpreter >> result) || !(interpreter >> std::ws).eof()) {
        throw std::runtime_error{"to<>() failed"};
    }
    return result;
}

// Usage of function template
void test_to_function() {
    auto x1 = to<std::string, double>(1.2); // Explicitly specify both template arguments
    auto x2 = to<std::string>(1.2);         // Source deduced as double
    auto x3 = to<>(1.2);                    // Target defaulted to string, Source deduced as double
    auto x4 = to(1.2);                      // Simplified form, same as x3

    std::cout << "Converted values: " << x1 << ", " << x2 << ", " << x3 << ", " << x4 << "\n";
}

int main() {
    // Test function template
    try {
        test_to_function();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
