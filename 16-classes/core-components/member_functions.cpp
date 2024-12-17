#include <iostream>

struct MyClass {
    // Non-static member function
    void display() {
        std::cout << "Called non-static member function\n";
    }

    // Static member function
    static void staticDisplay() {
        std::cout << "Called static member function\n";
    }

    // Const member function
    void displayConst() const {
        std::cout << "Called const member function\n";
    }

    // Member function to demonstrate `this` pointer
    void callViaThis() {
        this->display();
    }
};

int main() {
    MyClass obj;                // Object of the class
    MyClass* objPtr = &obj;     // Pointer to the object
    MyClass& objRef = obj;      // Reference to the object
    const MyClass constObj;     // Const object

    // 1. Using an object (dot operator)
    obj.display();

    // 2. Using a pointer to an object (arrow operator)
    objPtr->display();

    // 3. Using a reference to an object
    objRef.display();

    // 4. Using `this` pointer
    obj.callViaThis();

    // 5. Using a pointer to member function
    auto funcPtr = &MyClass::display;

    // a) Pointer-to-member with object
    (obj.*funcPtr)();

    // b) Pointer-to-member with pointer to object
    (objPtr->*funcPtr)();

    // 6. Using static member functions
    MyClass::staticDisplay();

    // 7. Calling const member function (const object)
    constObj.displayConst();

    // 8. Using lambda or function pointer to call a member function
    auto lambda = [&obj]() { obj.display(); };  // Wrap member function in a lambda
    lambda();

    return 0;
}
