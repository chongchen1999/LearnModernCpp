#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>

// Custom exception classes.
struct Some_error {
    std::string message;
    Some_error(const std::string& msg) : message(msg) {}
    Some_error(Some_error &&other) noexcept
        : message(std::move(other.message)) {}
};

struct Range_error {
    std::string message;
    Range_error(const std::string& msg) : message(msg) {}
    Range_error(Range_error &&other) noexcept
        : message(std::move(other.message)) {}
};

// A function that may throw an exception.
int do_task(int value) {
    if (value >= 0 && value <= 100) {
        return value * 2; // Example success case.
    } else {
        auto e = Range_error{"Value out of range: " + std::to_string(value)};
        std::cout << static_cast<void *>(&e) << '\n';
        throw std::move(e);
    }
}

// A function that catches and handles exceptions.
void taskmaster() {
    try {
        int value = 150; // Example input.
        int result = do_task(value); // Attempt the task.
        std::cout << "Task completed successfully. Result: " << result << '\n';
    } catch (const Range_error& e) {
        std::cout << static_cast<const void *>(&e) << '\n';
        std::cerr << "Range Error: " << e.message << '\n';
    } catch (const Some_error& e) {
        std::cerr << "Some Error: " << e.message << '\n';
    } catch (...) {
        std::cerr << "An unknown error occurred.\n";
    }
}

// Entry point.
int main() {
    taskmaster();
    return 0;
}
