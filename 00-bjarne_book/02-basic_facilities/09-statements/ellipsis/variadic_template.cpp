#include <iostream>
#include <string>

// Function template to print all arguments
template<typename... Args>
void printAll(Args... args) {
    (std::cout << ... << args) << '\n'; // Fold expression (C++17)
}

int main() {
    printAll(1, 2.5, "Hello", std::string("World!"));
    return 0;
}
