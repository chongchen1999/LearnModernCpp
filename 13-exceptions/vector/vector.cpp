#include <iostream>
#include <string>
#include "vector.h" // Assuming the previous implementation is in vector.h

void printVector(const vector<int>& vec) {
    std::cout << "Vector contents: ";
    for (int x : vec) {
        std::cout << x << " ";
    }
    std::cout << "\nSize: " << vec.size() 
              << ", Capacity: " << vec.capacity() << std::endl;
}

int main() {
    // Default constructor
    vector<int> vec1;

    // Constructor with initial size and value
    vector<int> vec2(5, 42);
    std::cout << "Vector with 5 elements of value 42:" << std::endl;
    printVector(vec2);

    // Push back elements
    std::cout << "\nPushing back elements:" << std::endl;
    vec2.push_back(10);
    vec2.push_back(20);
    vec2.push_back(30);
    printVector(vec2);

    // Copy constructor
    vector<int> vec3 = vec2;
    std::cout << "\nCopied vector:" << std::endl;
    printVector(vec3);

    // Move constructor
    vector<int> vec4 = std::move(vec3);
    std::cout << "\nAfter move:" << std::endl;
    printVector(vec4);
    std::cout << "Original vector after move:" << std::endl;
    printVector(vec3); // Should be empty

    // Resize
    std::cout << "\nResizing vector:" << std::endl;
    vec4.resize(10, 100);
    printVector(vec4);

    // Reserve
    std::cout << "\nReserving space:" << std::endl;
    vec4.reserve(20);
    printVector(vec4);

    // Demonstrating exception safety with strings
    try {
        vector<std::string> strVec(3, "Hello");
        strVec.push_back("World");
        
        for (const auto& str : strVec) {
            std::cout << str << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}