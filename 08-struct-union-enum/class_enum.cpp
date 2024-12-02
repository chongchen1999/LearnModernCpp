#include <iostream>

enum class Warning {
    green,
    yellow,
    orange,
    red
};

int main() {
    auto x = Warning::green;
    std::cout << typeid(x).name() << std::endl;
    std::cout << static_cast<int>(x) << std::endl;
    // Verify the static cast values
    if (static_cast<int>(Warning::green) == 0) {
        std::cout << "Warning::green is 0\n";
    } else {
        std::cout << "Warning::green verification failed!\n";
    }

    if (static_cast<int>(Warning::yellow) == 1) {
        std::cout << "Warning::yellow is 1\n";
    } else {
        std::cout << "Warning::yellow verification failed!\n";
    }

    if (static_cast<int>(Warning::orange) == 2) {
        std::cout << "Warning::orange is 2\n";
    } else {
        std::cout << "Warning::orange verification failed!\n";
    }

    if (static_cast<int>(Warning::red) == 3) {
        std::cout << "Warning::red is 3\n";
    } else {
        std::cout << "Warning::red verification failed!\n";
    }

    return 0;
}
