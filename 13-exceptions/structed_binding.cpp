#include <iostream>

int main() {
    int arr[3] = {1, 2, 3};
    std::cout << static_cast<void *>(&arr[0]) << "\n"
        << static_cast<void *>(&arr[1]) << "\n"
        << static_cast<void *>(&arr[2]) << "\n";

    auto [a, b, c] = arr;  // Structured binding
    std::cout << typeid(a).name() << "\n";
    a = 10;
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << "\n";

    std::cout << static_cast<void *>(&a) << "\n"
        << static_cast<void *>(&b) << "\n"
        << static_cast<void *>(&c) << "\n";

    return 0;
}
