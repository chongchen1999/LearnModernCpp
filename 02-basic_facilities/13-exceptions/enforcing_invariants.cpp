#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace Assert {

// Modes for assertion handling
enum class Mode { throw_, terminate_, ignore_ };

// Current settings
constexpr Mode current_mode = Mode::throw_;
constexpr int current_level = 2;
constexpr int default_level = 1;

// Error class for exceptions
struct Error : std::runtime_error {
    explicit Error(const std::string& message) : std::runtime_error(message) {}
};

// Helper function to check debug levels
constexpr bool level(int n) { return n <= current_level; }

// Compose error messages with file and line information
std::string compose(const char* file, int line, const std::string& message) {
    std::ostringstream os;
    os << "(" << file << "," << line << "): " << message;
    return os.str();
}

// Assertion checking function
template <bool condition = level(default_level), class Except = Error>
void dynamic(bool assertion,
             const std::string& message = "Assert::dynamic failed") {
    if (assertion) return;

    if (current_mode == Mode::throw_) {
        throw Except{message};
    } else if (current_mode == Mode::terminate_) {
        std::terminate();
    }
}

// Specialization for ignored assertions
template <>
void dynamic<false, Error>(bool, const std::string&) {
    // Do nothing
}

}  // namespace Assert

// Example usage
void f(int n) {
    const int max = 10;  // Example maximum value

    // Check if n is in the range [1, max)
    Assert::dynamic<Assert::level(2), Assert::Error>(
        (n > 0 && n < max),
        Assert::compose(__FILE__, __LINE__, "range problem"));

    // ... Other code ...
}

int main() {
    try {
        f(0);  // Will throw an exception for failing the assertion
    } catch (const Assert::Error& e) {
        std::cerr << "Assertion failed: " << e.what() << '\n';
    }

    return 0;
}
