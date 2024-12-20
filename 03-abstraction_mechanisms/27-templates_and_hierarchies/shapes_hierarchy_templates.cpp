#include <cmath>
#include <iostream>

// Base class for configuration
class Configuration {
public:
    virtual ~Configuration() = default;
    // General interface for configuration
};

// Base class for shapes
class Shape {
    Configuration* config;

public:
    void setConfiguration(Configuration* cfg) {
        config = cfg;
    }

    template<typename Color_scheme, typename Canvas>
    void configure(const Color_scheme& color, const Canvas& canvas) {
        // Configure the shape
        std::cout << "Configuring shape with Color_scheme and Canvas\n";
    }

    virtual void draw() const = 0; // Abstract method
    virtual ~Shape() = default;
};

// Circle shape
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle\n";
    }
};

// Triangle shape
class Triangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Triangle\n";
    }
};

// Main function to demonstrate usage
int main() {
    Circle circle;
    Triangle triangle;

    // Example configuration
    circle.configure("RGB", "Bitmapped");
    triangle.configure("RGB", "Bitmapped");

    circle.draw();
    triangle.draw();

    return 0;
}
