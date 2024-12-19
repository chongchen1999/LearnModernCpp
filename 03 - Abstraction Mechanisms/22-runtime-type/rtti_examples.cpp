#include <iostream>
#include <typeinfo>
#include <vector>
#include <unordered_map>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void rotate() = 0;
};

class Circle : public Shape {
public:
    void rotate() override {
        // Circle rotation logic
    }
};

class Triangle : public Shape {
public:
    void rotate() override {
        // Triangle rotation logic
    }
};

class Ship {
    // Example class for template-based processing
};

// Proper RTTI usage example
void printType(const Shape& shape) {
    std::cout << "Type: " << typeid(shape).name() << "\n";
}

// Template-based processing for type safety
void processShips(std::vector<Ship*>& ships) {
    for (Ship* ship : ships) {
        // Process each ship
    }
}

int main() {
    Circle c;
    Triangle t;
    Shape* shape = &c;

    // Demonstrate RTTI
    printType(*shape);
    shape = &t;
    printType(*shape);

    // Template-based processing
    std::vector<Ship*> ships;
    Ship ship1, ship2;
    ships.push_back(&ship1);
    ships.push_back(&ship2);
    processShips(ships);

    return 0;
}
