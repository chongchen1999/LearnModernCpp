#include <iostream>

class Point {
    int x;
    int y;
public:
    Point() : x(0), y(0) {}
    // Overloading the << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
    // Overloading the >> operator for input
    friend std::istream& operator>>(std::istream& is, Point& point) {
        is >> point.x >> point.y;
        return is;
    }
};


int main() {
    Point p;
    std::cout << "Enter the x and y coordinates of the point: ";
    std::cin >> p;
    std::cout << "The point you entered is: " << p << std::endl;

    std::cout << static_cast<void*>(&std::cin) << std::endl;
    std::cout << sizeof(std::cin) << std::endl;

    return 0;
}