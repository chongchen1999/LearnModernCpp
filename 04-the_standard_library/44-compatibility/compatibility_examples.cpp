// compatibility_examples.cpp
// Demonstrates key differences between C and C++

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Example of extern "C" for C compatibility
extern "C" {
    // This function will use C linkage
    int c_style_function(int x) {
        return x * 2;
    }
}

// Modern C++ class example - not available in C
class ModernCppFeatures {
private:
    std::string name;
    std::vector<int> data;

public:
    // Constructor with initializer list
    ModernCppFeatures(std::string n) : name(std::move(n)) {}

    // C++11 range-based for loop
    void processData() {
        std::vector<int> numbers = {1, 2, 3, 4, 5};  // C++11 uniform initialization
        for (const auto& num : numbers) {  // C++11 range-for and auto
            data.push_back(num);
        }
    }

    // Lambda function example (C++11)
    void useLambda() {
        auto lambda = [this]() {
            std::cout << "Name: " << name << "\n";
        };
        lambda();
    }
};

// Demonstration of differences in string literals
void stringLiteralDifference() {
    // In C++, string literals are const char*
    const char* cpp_str = "Hello";  // Correct in C++
    // char* c_str = "Hello";  // Would be legal in C, but wrong in C++
    
    // Modern C++ string usage
    std::string modern_str = "Hello";
}

// Demonstration of nullptr (C++11) vs NULL
void pointerDifference() {
    // Modern C++ way
    int* ptr1 = nullptr;  // C++11 nullptr
    
    // Old C way
    // int* ptr2 = NULL;  // Not preferred in modern C++
}

// Example of C++ function overloading (not possible in C)
void print(int x) {
    std::cout << "Integer: " << x << "\n";
}

void print(const std::string& s) {
    std::cout << "String: " << s << "\n";
}

// Modern C++ memory management
void memoryManagementExample() {
    // C++ style (preferred)
    auto ptr = std::make_unique<int>(42);
    
    // C style (avoid in C++)
    // int* c_ptr = (int*)malloc(sizeof(int));
    // free(c_ptr);
}

// Example of const in C++
void constExample() {
    const int cpp_const = 42;  // Must be initialized in C++
    // const int c_const;  // Would be legal in C, but error in C++
}

int main() {
    // Demonstrate modern C++ features
    ModernCppFeatures demo("Test");
    demo.processData();
    demo.useLambda();
    
    // Demonstrate function overloading
    print(42);
    print("Hello");
    
    // Memory management
    memoryManagementExample();
    
    // Pointer safety
    pointerDifference();
    
    // String handling
    stringLiteralDifference();
    
    return 0;
}
