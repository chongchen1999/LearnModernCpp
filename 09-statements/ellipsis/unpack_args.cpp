#include <iostream>
#include <vector>

class MyClass {
    std::vector<int> values;

public:
    template<typename... Args>
    MyClass(Args... args) : values{args...} {} // Unpack args

    void print() {
        for (int v : values) {
            std::cout << v << " ";
        }
    }
};

int main() {
    MyClass obj(1, 2, 3, 4);
    obj.print();
    return 0;
}