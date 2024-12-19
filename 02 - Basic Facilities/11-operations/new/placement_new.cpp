#include <iostream>
#include <new> // For placement new

class X {
public:
    X(int value) : val(value) {
        std::cout << "X constructed with value: " << val << '\n';
    }
    ~X() {
        std::cout << "X destructed with value: " << val << '\n';
    }
private:
    int val;
};

int main() {
    // Allocate raw memory at a specific address
    char buffer[sizeof(X)]; // Memory buffer large enough for X
    void* memory = reinterpret_cast<void*>(buffer);

    // Use placement new to construct X in this memory
    X* obj = new (memory) X(42); // Placement new

    // Call destructor explicitly (manual cleanup for placement new)
    obj->~X();

    return 0;
}