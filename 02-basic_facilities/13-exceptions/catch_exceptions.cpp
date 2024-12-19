#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include <stdexcept>

class Base {};
class Derived : public Base {};

void catchingExceptions() {
    try {
        throw Derived{};
    } catch (Base&) {
        std::cout << "Caught Base\n";
    }
}

void catchByReference() {
    try {
        throw std::runtime_error("Example");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
}

void scopesInTryCatch() {
    int x1 = 10;
    try {
        int x2 = 20;
        std::cout << x2 << "\n";
    } catch (...) {
        std::cout << "Caught something\n";
    }
}

void rethrowExample() {
    try {
        throw std::runtime_error("Error");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
        throw;
    }
}

void catchAllExample() {
    try {
        throw 42;
    } catch (...) {
        std::cout << "Caught something\n";
    }
}

void multipleHandlers() {
    try {
        throw std::ios_base::failure("IO error");
    } catch (const std::ios_base::failure& e) {
        std::cout << "Caught IO error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Caught standard exception: " << e.what() << "\n";
    } catch (...) {
        std::cout << "Caught something\n";
    }
}

class X {
    std::vector<int> vi;
    std::vector<std::string> vs;

public:
    X(int sz1, int sz2) try : vi(sz1), vs(sz2) {
        std::cout << "Constructor succeeded\n";
    } catch (const std::exception& e) {
        std::cerr << "Constructor failed: " << e.what() << "\n";
        throw;
    }
};

int main() {
    catchingExceptions();
    catchByReference();
    scopesInTryCatch();
    try {
        rethrowExample();
    } catch (...) {
        std::cout << "Rethrown exception caught\n";
    }
    catchAllExample();
    multipleHandlers();
    try {
        X obj(10, 5);
    } catch (...) {
        std::cerr << "Exception in object construction\n";
    }
    return 0;
}
