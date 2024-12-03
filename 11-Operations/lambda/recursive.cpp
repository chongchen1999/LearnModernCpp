#include <iostream>
#include <functional>

int f(int x, int y) {
    return x + y;
}

int main() {
    // Recursive lambda for computing factorial
    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    };

    std::cout << "Factorial of 5: " << factorial(5) << "\n";

    int (*g)(int, int) = f;
    std::cout << "g(3, 4): " << g(3, 4) << "\n";

    return 0;
}
