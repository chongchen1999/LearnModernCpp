#include <iostream>

int main() {
    float x = 10.5;
    const int &y = x;
    std::cout << x << " " << y << std::endl;
    return 0;
}