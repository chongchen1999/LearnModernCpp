#include <iostream>
#include <vector>
#include <stdexcept>
#include <exception>

// Custom exception class
struct MyError : public std::runtime_error {
    explicit MyError(const std::string& message)
        : std::runtime_error(message) {}
};

// Function demonstrating propagation
void propagateException() {
    try {
        throw std::runtime_error("Error in thread");
    } catch (...) {
        auto ep = std::current_exception(); // Capture exception
        std::rethrow_exception(ep);         // Re-throw exception
    }
}

// Function demonstrating nested exceptions
void myFunction() {
    try {
        throw std::runtime_error("Inner exception");
    } catch (...) {
        std::throw_with_nested(std::logic_error("Outer exception"));
    }
}

int main() {
    try {
        // Example: Container exception
        std::vector<int> v = {1, 2, 3};
        std::cout << v.at(5);
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught exception: " << e.what() << '\n';
    }

    try {
        // Example: Custom exception
        throw MyError("Custom error occurred!");
    } catch (const MyError& e) {
        std::cerr << "Caught custom exception: " << e.what() << '\n';
    }

    try {
        // Example: Propagation
        propagateException();
    } catch (const std::exception& e) {
        std::cerr << "Propagated exception: " << e.what() << '\n';
    }

    try {
        // Example: Nested exceptions
        myFunction();
    } catch (const std::exception& e) {
        std::cerr << "Caught: " << e.what() << '\n';
        try {
            std::rethrow_if_nested(e);
        } catch (const std::exception& nested) {
            std::cerr << "Nested: " << nested.what() << '\n';
        }
    }

    return 0;
}
