#include <iostream>
#include "calculator.h"

int main() {
    using namespace Calculator;

    double x = 10.5, y = 2.5;

    std::cout << "Addition: " << add(x, y) << '\n';
    std::cout << "Subtraction: " << subtract(x, y) << '\n';
    std::cout << "Multiplication: " << multiply(x, y) << '\n';

    try {
        std::cout << "Division: " << divide(x, y) << '\n';
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
