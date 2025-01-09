#include <limits>
#include <iostream>

int main() {
    int a = std::numeric_limits<int>::max();
    int b = a + 1;
    std::cout << a << " " << b << std::endl;
    return 0;
}