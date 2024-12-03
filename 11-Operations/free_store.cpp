#include <iostream>
#include <cstddef>
#include <string>

class MyClass {
private:
    std::string name;
    int age;
public:
    void* operator new(size_t size) {
        std::cout << "Custom new for size: " << size << '\n';
        return ::operator new(size); // Use global operator new
    }

    void operator delete(void* ptr) {
        std::cout << "Custom delete\n";
        ::operator delete(ptr); // Use global operator delete
    }
};

int main() {
    std::cout << sizeof(std::string) << '\n';
    MyClass* obj = new MyClass(); // Custom new is called
    delete obj;                   // Custom delete is called
    return 0;
}
