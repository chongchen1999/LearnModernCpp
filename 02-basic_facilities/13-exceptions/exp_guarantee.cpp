#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

// Points Namespace Example
namespace Points {
    std::vector<int> vx;
    std::vector<int> vy;

    void add_point(int x, int y) {
        vx.push_back(x);
        vy.push_back(y);
    }

    void remove_last_point() {
        if (!vx.empty()) {
            vx.pop_back();
            vy.pop_back();
        }
    }
}

// Exception-Safe Resource Management
void safe_function(int i) {
    auto p = std::make_unique<int[]>(10);  // Managed memory
    if (i < 0) {
        throw std::runtime_error("Negative value!");
    }
}

// Strong Guarantee Example
void test_vector() {
    std::vector<int> vec;
    std::cout << "Vector size: " << sizeof(std::vector<double>) << '\n';
    try {
        vec.push_back(10);  // Strong guarantee
    } catch (...) {
        std::cerr << "Exception caught!\n";
    }
}

int main() {
    try {
        Points::add_point(1, 2);
        Points::remove_last_point();

        safe_function(5);
        test_vector();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
