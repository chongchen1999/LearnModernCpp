#include <iostream>

template <typename T>
class A {
    public:
    void display() {
        std::cout << "Primary template for A" << std::endl;
        std::cout << "T = " << typeid(T).name() << std::endl;
    }
};

int main() {
    A<double>{}.display();
    return 0;
}