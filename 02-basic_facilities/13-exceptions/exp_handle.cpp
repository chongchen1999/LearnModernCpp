#include <iostream>
#include <cmath>
#include <cerrno>
#include <stdexcept>

// 1. Traditional Error Handling

// Terminate the Program
void terminate_example() {
    bool something_wrong = true;
    if (something_wrong) exit(1); // Terminates program
}

// Return an Error Value
int get_int(bool fail) {
    if (fail) return -1; // Error value
    return 42;
}

// Return a Legal Value and Set an Error State
double safe_sqrt(double x) {
    errno = 0; // Reset errno
    double result = sqrt(x);
    if (errno != 0) {
        std::cerr << "Error: invalid input for sqrt()\n";
        return -1;
    }
    return result;
}

// Call an Error-Handler Function
void handle_error() {
    std::cerr << "An error occurred!\n";
}

void call_handler_example() {
    bool something_wrong = true;
    if (something_wrong) handle_error();
}

// 2. Exception Handling

void process(int value) {
    if (value < 0) {
        auto e = std::invalid_argument("Negative value not allowed");
        std::cout << static_cast<void *>(&e) << std::endl;
        throw std::move(e);
    }
    // Normal processing here
}

void exception_handling_example() {
    try {
        process(-1); // Throws an exception
    } catch (const std::invalid_argument &e) {
        std::cout << static_cast<const void *>(&e) << std::endl;
        std::cerr << "Caught exception: " << e.what() << '\n';
    }
}

// Main Function
int main() {
    // Traditional methods
    std::cout << "Return error value: " << get_int(false) << '\n';
    std::cout << "Safe sqrt: " << safe_sqrt(-1.0) << '\n';
    call_handler_example();

    // Exception handling
    exception_handling_example();

    return 0;
}
