#include <iostream>
#include <utility> // for std::move

class MyClass {
private:
    int* data;

public:
    MyClass(int value) {
        data = new int(value);
        std::cout << "Constructor: Allocated resource with value " << *data << std::endl;
    }

    MyClass(const MyClass& other) {
        data = new int(*other.data);
        std::cout << "Copy Constructor: Deep copied resource with value " << *data << std::endl;
    }

    MyClass(MyClass&& other) noexcept {
        data = other.data;
        other.data = nullptr;
        std::cout << "Move Constructor: Moved resource" << std::endl;
    }

    MyClass& operator=(const MyClass& other) {
        if (this == &other) return *this;
        delete data;
        data = new int(*other.data);
        std::cout << "Copy Assignment: Deep copied resource with value " << *data << std::endl;
        return *this;
    }

    MyClass& operator=(MyClass&& other) noexcept {
        if (this == &other) return *this;
        delete data;
        data = other.data;
        other.data = nullptr;
        std::cout << "Move Assignment: Moved resource" << std::endl;
        return *this;
    }

    ~MyClass() {
        if (data) std::cout << "Destructor: Releasing resource with value " << *data << std::endl;
        else std::cout << "Destructor: No resource to release (moved-from state)" << std::endl;
        delete data;
    }

    void print() const {
        if (data) std::cout << "Resource value: " << *data << std::endl;
        else std::cout << "Resource is in a moved-from state" << std::endl;
    }
};

int main() {
    std::cout << "Creating object a:\n";
    MyClass a(10);

    std::cout << "\nCopying object a to b:\n";
    MyClass b = a;

    std::cout << "\nMoving object a to c:\n";
    MyClass c = std::move(a);

    std::cout << "\nState of a after move:\n";
    a.print();

    std::cout << "\nAssigning b to c (copy assignment):\n";
    c = b;

    std::cout << "\nMoving b to c (move assignment):\n";
    c = std::move(b);

    std::cout << "\nState of b after move:\n";
    b.print();

    std::cout << "\nExiting program:\n";
    return 0;
}
