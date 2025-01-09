#include <cassert>
#include <iostream>
#include <vector>
#include <type_traits>
#include <system_error>
#include <string>
#include <fstream>

// ======== Section 1: Assertions with `static_assert` and `assert` ========

// Shape hierarchy for `static_assert` example
struct Shape {};
struct Circle : public Shape {};
struct NotAShape {};

template<typename T>
void draw_all(std::vector<T*>& v) {
    // Compile-time check
    static_assert(std::is_base_of<Shape, T>::value, "non-Shape type for draw_all()");
    
    for (auto p : v) {
        // Runtime check
        assert(p != nullptr && "Null pointer encountered");
        std::cout << "Drawing shape\n";
    }
}

void test_assertions() {
    Circle c1, c2;
    std::vector<Circle*> shapes = {&c1, &c2};
    draw_all(shapes);

    // Uncomment the following lines to see the static_assert error
    // NotAShape nas;
    // std::vector<NotAShape*> invalid_shapes = {&nas};
    // draw_all(invalid_shapes);
}

// ======== Section 2: System Error Handling with `error_code` ========

std::ostream& open_file(const std::string& path) {
    // Mock error code for demonstration (replace with real logic)
    std::error_code err = std::make_error_code(std::errc::no_such_file_or_directory);

    if (err) {
        if (err == std::errc::permission_denied) {
            std::cerr << "Error: Permission denied for path: " << path << '\n';
        } else if (err == std::errc::not_a_directory) {
            std::cerr << "Error: Not a directory: " << path << '\n';
        } else {
            throw std::system_error(err, "Unable to access path");
        }
    }

    std::cout << "File opened successfully: " << path << '\n';
    return std::cout;
}

void test_error_handling() {
    try {
        open_file("/invalid/path");
    } catch (const std::system_error& e) {
        std::cerr << "Caught system_error: " << e.what() << '\n';
        std::cerr << "Error category: " << e.code().category().name() << '\n';
        std::cerr << "Error message: " << e.code().message() << '\n';
    }
}

// ======== Section 3: Custom Error Categories ========

enum class MyErrorCode {
    Error1 = 1,
    Error2,
    Error3
};

class MyErrorCategory : public std::error_category {
public:
    const char* name() const noexcept override {
        return "MyErrorCategory";
    }

    std::string message(int ev) const override {
        switch (static_cast<MyErrorCode>(ev)) {
            case MyErrorCode::Error1: return "Error 1 occurred";
            case MyErrorCode::Error2: return "Error 2 occurred";
            case MyErrorCode::Error3: return "Error 3 occurred";
            default: return "Unknown error";
        }
    }
};

const std::error_category& my_error_category() {
    static MyErrorCategory category;
    return category;
}

std::error_code make_error_code(MyErrorCode e) {
    return {static_cast<int>(e), my_error_category()};
}

// Enable usage with error_code
namespace std {
template <>
struct is_error_code_enum<MyErrorCode> : true_type {};
}

void test_custom_error_category() {
    std::error_code ec = MyErrorCode::Error2;

    std::cout << "Error category: " << ec.category().name() << '\n';
    std::cout << "Error message: " << ec.message() << '\n';
}

// ======== Main Function ========

int main() {
    // Uncomment the following lines to test each section

    // Section 1: Test Assertions
    std::cout << "Testing Assertions...\n";
    test_assertions();

    // Section 2: Test System Error Handling
    std::cout << "\nTesting System Error Handling...\n";
    test_error_handling();

    // Section 3: Test Custom Error Categories
    std::cout << "\nTesting Custom Error Categories...\n";
    test_custom_error_category();

    return 0;
}
