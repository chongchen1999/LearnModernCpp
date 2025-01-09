#include "swap.h"
#include "add.h"
#include <iostream>

int main() {
    int a = 10;
    int b = 20;

    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swap<int>(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;

    std::cout << "Before add: a = " << a << ", b = " << b << std::endl;
    std::cout << "Sum = " << add<int>(a, b) << std::endl;

    return 0;
}