#include <iostream>

class B1 {
public:
    B1() { std::cout << "B1 default constructor\n"; }
};

class B2 {
    int value;
public:
    B2(int v) : value{v} { std::cout << "B2 parameterized constructor with value: " << value << "\n"; }
};

struct D1 : B1, B2 {
    D1(int i) : B1{}, B2{i} { std::cout << "D1 constructor\n"; }
};

struct D2 : B1, B2 {
    D2(int i) : B2{i} { 
        std::cout << "D2 constructor\n"; 
    }
    // B1 default constructor is implicitly called
};

int main() {
    std::cout << "Creating D1:\n";
    D1 d1{42};

    std::cout << "\nCreating D2:\n";
    D2 d2{99};

    return 0;
}
