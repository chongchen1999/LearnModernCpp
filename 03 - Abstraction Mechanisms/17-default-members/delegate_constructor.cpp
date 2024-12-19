#include <string>
#include <stdexcept>

// Mocking required functions and classes
int max = 100; // Example max value

class Bad_X : public std::runtime_error {
public:
    Bad_X(int x) : std::runtime_error("Bad value for X: " + std::to_string(x)) { }
};

template<typename T>
T to(const std::string& s) {
    return std::stoi(s); // Example implementation for converting string to int
}

class X {
    int a;

public:
    // Primary constructor
    X(int x) {
        if (0 < x && x <= max)
            a = x;
        else
            throw Bad_X(x);
    }

    // Delegating constructors
    X() : X{42} { } // Delegates to X(int)
    X(std::string s) : X{to<int>(s)} { } // Delegates to X(int)

    // Alternative: Member initializer example
    X(bool useDefault) : a{42} { } // Uses direct member initialization
};
