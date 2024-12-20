#include <concepts>
#include <iostream>
#include <type_traits>

// Define a concept to check if one type is convertible to another
template <typename From, typename To>
concept Convertible = std::is_convertible_v<From, To>;

// Pointer wrapper class
template <typename T>
class Ptr {
    T* p; // Pointer to T
public:
    // Constructor to initialize the pointer
    explicit Ptr(T* ptr = nullptr) : p(ptr) {}

    // Conversion operator using the Convertible concept
    template <typename T2>
    requires Convertible<T*, T2*>
    explicit operator Ptr<T2>() const {
        return Ptr<T2>{p};
    }

    // Method to access the raw pointer
    T* get() const { return p; }
    T& operator*() const { return *p; }
    T* operator->() const { return p; }
};

// Example classes to demonstrate the concept
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const { std::cout << "Drawing a Shape\n"; }
};

class Circle : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Circle\n"; }
};

class Triangle : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Triangle\n"; }
};

// Function to demonstrate the usage of Ptr
void exampleConversion() {
    // Create a Ptr to Circle
    Ptr<Circle> pc(new Circle());

    // Convert Ptr<Circle> to Ptr<Shape> using the conversion operator
    Ptr<Shape> ps = static_cast<Ptr<Shape>>(pc); // OK: Circle* -> Shape*

    // Access and use the Shape pointer
    ps.get()->draw();
    ps->draw();
    (*ps).draw();

    // Try an invalid conversion (uncomment to see the error)
    // Ptr<Circle> pc2 = static_cast<Ptr<Circle>>(ps); // Error: Shape* -> Circle* not valid
}

int main() {
    exampleConversion();
    return 0;
}
