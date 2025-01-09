#include <iostream>

template <typename Derived>
class Interface {
public:
    void run() {
        static_cast<Derived*>(this)->run();
    }
};

class Implementation : public Interface<Implementation> {
public:
    void run() {
        std::cout << "Implementation running\n";
    }
};

template <typename Derived>
class Animal {
public:
    void speak() {
        static_cast<Derived*>(this)->makeSound();
    }
};

class Dog : public Animal<Dog> {
public:
    void makeSound() {
        std::cout << "Woof!\n";
    }
};

class Cat : public Animal<Cat> {
public:
    void makeSound() {
        std::cout << "Meow!\n";
    }
};

template <typename Derived>
class Logger {
public:
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << "\n";
    }
};

class MyApplication : public Logger<MyApplication> {
public:
    void run() {
        log("Application is running");
    }
};

int main() {
    Implementation impl;
    impl.run(); // Output: Implementation running

    Dog dog;
    Cat cat;

    dog.speak(); // Output: Woof!
    cat.speak(); // Output: Meow!

    MyApplication app;
    app.run(); // Output: [LOG] Application is running

}
