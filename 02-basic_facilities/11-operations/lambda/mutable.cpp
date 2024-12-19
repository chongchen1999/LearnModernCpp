#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int count = 5;

    // Mutable lambda allows modification of captured variables by value
    auto decrementer = [count]() mutable {
        return --count;
    };

    for (int i = 0; i < 5; ++i) {
        std::cout << decrementer() << " ";
    }
    std::cout << "\n";

    return 0;
}
