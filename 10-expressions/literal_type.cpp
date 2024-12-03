// A class with a constexpr constructor is called a literal type
#include <cmath>
#include <iostream>

int f(int x) {
    return x * x;
}

struct Point {
    int x, y, z;

    // constexpr constructor
    constexpr Point(int x_val, int y_val, int z_val)
        : x(x_val), y(y_val), z(z_val) {}

    // constexpr member function
    constexpr Point up(int d) const { return Point(x, y, z + d); }
    constexpr Point move(int dx, int dy) const { return Point(x + dx, y + dy, z); }
};

int main() {
    constexpr Point origo {0, 0, 0}; // A Point initialized at the origin
    constexpr int z = origo.x;       // Accessing member 'x' at compile time

    constexpr Point a[] = {
        origo, Point{1, 1, 1}, Point{2, 2, static_cast<int>(sqrt(4))}, origo.move(3, 3)
    };
    constexpr int x = a[1].x;  // Accessing the 'x' value of the second element in array 'a'
    // x becomes 1

    if (int x, y, z; std::cin >> x >> y >> z) {
        std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
        z = sqrt(4);
        Point p{x, y, z};
    }

    if (double x; x = sqrt(2)) {
        std::cout << "sqrt(2) = " << f(x) << std::endl;
    }

    return 0;
}