#include <iostream>
#include <memory>

using namespace std;

// A simple class to demonstrate behavior
class Resource {
public:
    void say_hello() const {
        cout << "Hello from Resource!\n";
    }
};

// Smart pointer class
template<typename T>
class SmartPtr {
public:
    T* ptr;  // Raw pointer to manage

public:
    // Constructor
    SmartPtr(T* p = nullptr) : ptr(p) { }

    // Destructor
    ~SmartPtr() {
        delete ptr;
    }

    // Overloaded operator-> (provides member access)
    T* operator->() {
        return ptr;  // Return the raw pointer
    }

    // Overloaded operator* (provides dereferencing)
    T& operator*() {
        return *ptr;  // Dereference the raw pointer
    }
};

int main() {
    // Create a SmartPtr to manage a Resource object
    SmartPtr<Resource> sp(new Resource);

    // Use overloaded operator-> to call a method
    sp.operator->()->say_hello();
    sp->say_hello();
    sp.ptr->say_hello();

    // Use overloaded operator* to get the actual object
    (*sp).say_hello();
    sp.operator*().say_hello();
    (*sp.ptr).say_hello();

    return 0;
}
