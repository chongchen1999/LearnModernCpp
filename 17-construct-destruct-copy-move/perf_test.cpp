#include <iostream>
#include <vector>
#include <chrono> // For timing
#include <string>

// Class with Move Constructor and Move Assignment marked noexcept
struct WithNoexcept {
    std::string* data;

    // Constructor
    WithNoexcept(const std::string& str) : data(new std::string(str)) {}

    // Destructor (to clean up the allocated memory)
    ~WithNoexcept() { delete data; }

    // Move Constructor (noexcept)
    WithNoexcept(WithNoexcept&& other) noexcept : data(other.data) {
        other.data = nullptr; // Transfer ownership
    }

    // Move Assignment (noexcept)
    WithNoexcept& operator=(WithNoexcept&& other) noexcept {
        if (this != &other) {
            delete data;          // Clean up current resource
            data = other.data;    // Transfer ownership
            other.data = nullptr; // Invalidate source
        }
        return *this;
    }

    // Copy constructor and assignment operator deleted to ensure moves are tested
    WithNoexcept(const WithNoexcept&) = delete;
    WithNoexcept& operator=(const WithNoexcept&) = delete;
};

// Class with Move Constructor and Move Assignment *not* marked noexcept
struct WithoutNoexcept {
    std::string* data;

    // Constructor
    WithoutNoexcept(const std::string& str) : data(new std::string(str)) {}

    // Destructor (to clean up the allocated memory)
    ~WithoutNoexcept() { delete data; }

    // Move Constructor (no noexcept)
    WithoutNoexcept(WithoutNoexcept&& other) : data(other.data) {
        other.data = nullptr; // Transfer ownership
    }

    // Move Assignment (no noexcept)
    WithoutNoexcept& operator=(WithoutNoexcept&& other) {
        if (this != &other) {
            delete data;          // Clean up current resource
            data = other.data;    // Transfer ownership
            other.data = nullptr; // Invalidate source
        }
        return *this;
    }

    // Copy constructor and assignment operator deleted to ensure moves are tested
    WithoutNoexcept(const WithoutNoexcept&) = delete;
    WithoutNoexcept& operator=(const WithoutNoexcept&) = delete;
};

// Function to measure time for vector operations
template <typename T>
void measure_performance(const std::string& test_name) {
    std::vector<T> vec;
    vec.reserve(1000000); // Reserve space for 1 million elements

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        vec.emplace_back("Test Data"); // Add objects to the vector
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << test_name << " took " << duration.count() << " seconds.\n";
}

int main() {
    std::cout << "Performance Test: noexcept vs no-noexcept in Move Operations\n";

    // Measure performance for WithoutNoexcept
    measure_performance<WithoutNoexcept>("Without noexcept");

    // Measure performance for WithNoexcept
    measure_performance<WithNoexcept>("With noexcept");

    return 0;
}
