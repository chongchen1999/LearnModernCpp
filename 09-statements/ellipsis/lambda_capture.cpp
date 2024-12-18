#include <iostream>
#include <tuple>

template<typename... Args>
void capturePack(Args... args) {
    auto lambda = [=]() { 
        ((std::cout << args << " "), ...); 
    }; // Fold expression
    lambda();
}

int main() {
    capturePack(1, 2, 3, 4.5, "Hello");
    return 0;
}
