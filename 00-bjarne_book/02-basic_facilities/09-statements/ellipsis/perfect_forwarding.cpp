#include <iostream>
#include <utility>

template<typename... Args>
void forwarder(Args&&... args) {
    // Forward arguments to another function
    auto lambda = [](auto&&... innerArgs) {
        ((std::cout << innerArgs << " "), ...);
    };
    lambda(std::forward<Args>(args)...);
}

int main() {
    forwarder(1, "example", 3.14);
    return 0;
}