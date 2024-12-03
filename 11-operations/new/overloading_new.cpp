#include <iostream>
#include <cstdlib> // For malloc and free

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

// Overload global new operator
void* operator new(size_t size) {
    std::cout << "Custom new called with size: " << size << '\n';
    void* ptr = ::malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}

// Overload global delete operator
void operator delete(void* ptr) noexcept {
    std::cout << "Custom delete called\n";
    ::free(ptr);
}

int main() {
    // Use the overloaded new operator
    X* obj = new X(42);

    // Use the overloaded delete operator
    delete obj;

    return 0;
}