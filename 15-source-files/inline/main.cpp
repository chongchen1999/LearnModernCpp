#include <iostream>
#include "a.h"
int main() {
    extern int x;
    // extern int y;
    std::cout << x << std::endl;
    // std::cout << y << std::endl;
    return 0;
}