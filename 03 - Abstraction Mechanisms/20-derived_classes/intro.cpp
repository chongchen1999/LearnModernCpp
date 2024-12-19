#include <iostream>
#include <string>

// Base class
class Shape {
public:
    virtual void draw() const { // Virtual function for runtime polymorphism
        std::cout << "Drawing a shape\n";
    }

    virtual ~Shape() = default; // Virtual destructor for proper cleanup
};

// Derived class: Circle
class Circle : public Shape {
public:
    void draw() const override { // Overriding the base class function
        std::cout << "Drawing a circle\n";
    }
};

// Derived class: Triangle
class Triangle : public Shape {
public:
    void draw() const override { // Overriding the base class function
        std::cout << "Drawing a triangle\n";
    }
};

// Base class for 2D objects
class TwoDimensional {
public:
    virtual void area() const = 0; // Pure virtual function
};

// Base class for rendering capabilities
class Renderable {
public:
    virtual void render() const = 0; // Pure virtual function
};

// Derived class combining multiple inheritance
class Rectangle : public TwoDimensional, public Renderable {
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    void area() const override {
        std::cout << "Area of rectangle: " << width * height << "\n";
    }

    void render() const override {
        std::cout << "Rendering rectangle...\n";
    }
};

// Function demonstrating runtime polymorphism
void renderShape(const Shape& shape) {
    shape.draw(); // Calls the appropriate draw() method based on the actual object type
}

int main() {
    Circle c;
    Triangle t;
    Rectangle rect(10, 5);

    // Render shapes using the base class interface
    renderShape(c); // Output: Drawing a circle
    renderShape(t); // Output: Drawing a triangle

    // Demonstrate multiple inheritance functionality
    rect.area();     // Output: Area of rectangle: 50
    rect.render();   // Output: Rendering rectangle...

    return 0;
}
