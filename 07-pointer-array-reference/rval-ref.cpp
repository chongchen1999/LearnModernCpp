#include <iostream>
int main() {
    std::cout << "S" << std::endl;
    int x = 10;
    int &y = x;
    using ref2int = int &;
    using refref2int = ref2int &;
    refref2int r = x;

    std::cout << x << ' ' << typeid(x).name() << std::endl;
    std::cout << y << ' ' << typeid(y).name() << std::endl;
    std::cout << r << ' ' << typeid(r).name() << std::endl;
    return 0;
}