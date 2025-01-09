// file: iostream_error_handling.cpp

#include <iostream>
#include <string>
#include <stdexcept>

// Function to demonstrate using streams as conditions
void read_values() {
    int x;
    while (std::cin >> x) {
        std::cout << "Read: " << x << std::endl;
    }
}

// Function to demonstrate recovering from errors
void recover_from_error() {
    int i;
    if (std::cin >> i) {
        std::cout << "Read integer: " << i << std::endl;
    } else if (std::cin.fail()) {
        std::cin.clear(); // Clear the fail state
        std::string s;
        if (std::cin >> s) {
            std::cout << "Read string instead: " << s << std::endl;
        }
    }
}

// Function to demonstrate handling exceptions
void use_exceptions() {
    try {
        std::cin.exceptions(std::ios_base::badbit);
        int x;
        while (std::cin >> x) {
            std::cout << "Read: " << x << std::endl;
        }
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Stream error: " << e.what() << std::endl;
    }
}

// RAII class for managing stream exceptions
struct Io_guard {
    std::ios& stream;
    std::ios::iostate old_state;

    Io_guard(std::ios& s, std::ios::iostate exc_state)
        : stream{s}, old_state{s.exceptions()} {
        stream.exceptions(stream.exceptions() | exc_state);
    }

    ~Io_guard() {
        stream.exceptions(old_state);
    }
};

// Function to demonstrate using RAII for exception management
void test_raii() {
    try {
        Io_guard guard(std::cin, std::ios_base::badbit);
        int x;
        while (std::cin >> x) {
            std::cout << "Read: " << x << std::endl;
        }
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Stream error with RAII: " << e.what() << std::endl;
    }
}

int main() {
    // Uncomment one of the following functions to test

    read_values();
    recover_from_error();
    use_exceptions();
    test_raii();

    return 0;
}
