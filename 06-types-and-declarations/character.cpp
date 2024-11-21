#include <iostream>

void intval() {
    for (char c; std::cin >> c; ) {
        std::cout << "the value of '" << c << "' is " << int{c} << '\n';
    }
}

int main() { 
    intval(); 
    return 0;
}