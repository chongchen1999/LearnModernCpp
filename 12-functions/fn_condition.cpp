#include <iostream>
#include <stdexcept> // For exceptions
#include <limits>    // For numeric_limits
#include <cassert>   // For assertions

// Function to calculate the area of a rectangle
int area(int len, int wid)
/*
Precondition: `len` and `wid` are positive integers.
Postcondition: Returns the area of a rectangle with sides `len` and `wid`.
               The result must be a positive integer.
*/
{
    // Check the precondition
    if (len <= 0 || wid <= 0) {
        throw std::invalid_argument("Length and width must be positive integers.");
    }

    // Calculate the area
    int result = len * wid;

    // Check for overflow (postcondition)
    if (result < 0) {
        throw std::overflow_error("Resulting area caused an overflow.");
    }

    // Postcondition: Correctness of the result
    return result;
}

// Alternative: Function to calculate area without checking preconditions
int area_no_check(int len, int wid) {
    return len * wid; // Assumes `len > 0` and `wid > 0`.
}

// Alternative: Function to calculate area that handles invalid inputs gracefully
int safe_area(int len, int wid) {
    if (len <= 0 || wid <= 0) return 0; // Treat invalid inputs as zero area
    return len * wid;
}

// Rectangle class to demonstrate functions with side effects
class Rectangle {
    int length, width;

public:
    void setLength(int len) {
        // Precondition: `len` must be positive
        if (len <= 0) throw std::invalid_argument("Length must be positive");
        length = len; // Postcondition: `length` is updated
    }

    void setWidth(int wid) {
        // Precondition: `wid` must be positive
        if (wid <= 0) throw std::invalid_argument("Width must be positive");
        width = wid; // Postcondition: `width` is updated
    }

    int calculateArea() {
        // Postcondition: Returns the area of the rectangle
        return length * width;
    }
};

int main() {
    try {
        std::cout << "Valid Area: " << area(10, 5) << "\n"; // Valid call

        // Invalid call to demonstrate precondition violation
        std::cout << "Invalid Area: " << area(-2, 5) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Example of overflow
    try {
        int large_value = std::numeric_limits<int>::max();
        std::cout << std::numeric_limits<unsigned int>::max() << "\n";
        std::cout << std::numeric_limits<long>::max() << "\n";
        std::cout << "Overflow Area: " << area(large_value, 2) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Using area_no_check (no precondition check)
    std::cout << "Area without checks (unsafe): " << area_no_check(10, 5) << "\n";

    // Using safe_area (handles invalid inputs gracefully)
    std::cout << "Safe Area with invalid input: " << safe_area(-10, 5) << "\n";

    // Demonstrating the Rectangle class
    try {
        Rectangle rect;
        rect.setLength(10);   // Valid call
        rect.setWidth(5);     // Valid call
        std::cout << "Rectangle Area: " << rect.calculateArea() << "\n";

        // Invalid call to setLength to demonstrate precondition violation
        rect.setLength(-10);
    } catch (const std::exception& e) {
        std::cerr << "Error in Rectangle: " << e.what() << "\n";
    }

    return 0;
}
