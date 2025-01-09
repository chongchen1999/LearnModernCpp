#include <iostream>
#include <utility> // For std::move
#include <string>

class X {
public:
    // Ordinary constructor
    X(const std::string& val) : data{new std::string(val)} {
        std::cout << "Ordinary Constructor: " << *data << '\n';
    }

    // Default constructor
    X() : data{new std::string("default")} {
        std::cout << "Default Constructor: " << *data << '\n';
    }

    // Copy constructor
    X(const X& other) : data{new std::string(*other.data)} {
        std::cout << "Copy Constructor: " << *data << '\n';
    }

    // Move constructor
    X(X&& other) noexcept : data{other.data} {
        other.data = nullptr;
        std::cout << "Move Constructor: moved resource\n";
    }

    // Copy assignment operator
    X& operator=(const X& other) {
        if (this == &other) return *this; // Self-assignment guard
        *data = *other.data;
        std::cout << "Copy Assignment: " << *data << '\n';
        return *this;
    }

    // Move assignment operator
    X& operator=(X&& other) noexcept {
        if (this == &other) return *this; // Self-assignment guard
        delete data;       // Clean up old resource
        data = other.data; // Move resource
        other.data = nullptr;
        std::cout << "Move Assignment: moved resource\n";
        return *this;
    }

    // Destructor
    ~X() {
        if (data) {
            std::cout << "Destructor: deleting " << *data << '\n';
        } else {
            std::cout << "Destructor: null resource\n";
        }
        delete data;
    }

    void print() const {
        if (data)
            std::cout << "Value: " << *data << '\n';
        else
            std::cout << "Value: null\n";
    }

private:
    std::string* data;
};

X createX(const std::string& val) {
    return X(val); // Return value optimization (RVO) may apply
}

int main() {
    std::cout << "=== Step 1: Constructors ===\n";
    X a{"Hello"}; // Ordinary constructor
    X b;          // Default constructor

    std::cout << "\n=== Step 2: Copy Constructor ===\n";
    X c = a; // Copy constructor

    std::cout << "\n=== Step 3: Copy Assignment ===\n";
    b = c; // Copy assignment operator

    std::cout << "\n=== Step 4: Move Constructor ===\n";
    X d = createX("World"); // Move constructor

    std::cout << "\n=== Step 5: Move Assignment ===\n";
    d = std::move(a); // Move assignment operator

    std::cout << "\n=== Step 6: Destructor ===\n";
    // All destructors are called automatically here as objects go out of scope

    return 0;
}
