#include <iostream>

enum class Color { red, blue, green };

int main() {
    using enum Color;  // 使用 using enum 来避免写 Color::

    Color color = red;

    switch (color) {
        case red:
            std::cout << "Hello" << std::endl;
            [[fallthrough]];  // 防止编译器对 fallthrough 发出警告
        case green:
            std::cout << "Hello" << std::endl;
            break;
        case blue:
            std::cout << "World" << std::endl;
            break;
        default:
            break;
    }

    return 0;
}
