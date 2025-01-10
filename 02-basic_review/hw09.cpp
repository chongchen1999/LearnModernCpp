#include <cmath>
#include <compare>  // For spaceship operator
#include <iostream>

class [[nodiscard]] Vector3 {
   public:
    float x{}, y{}, z{};

    // Constructors
    Vector3() : x(0), y(0), z(0) {}                  // Default constructor
    explicit Vector3(float x) : x(x), y(0), z(0) {}  // Single value constructor
    Vector3(float x, float y) : x(x), y(y), z(0) {}  // Two values constructor
    Vector3(float x, float y, float z)
        : x(x), y(y), z(z) {}  // Full initialization

    // Operator +
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Operator +=
    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // Comparison operators using spaceship operator
    auto operator<=>(const Vector3& other) const {
        return length_squared() <=> other.length_squared();
    }

    bool operator==(const Vector3& other) const = default;

   private:
    float length_squared() const { return x * x + y * y + z * z; }
};

// Global operator+ for commutative addition
Vector3 operator+(float scalar, const Vector3& vec) {
    return Vector3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

// Test function
int main() {
    Vector3 vec1;           // (0, 0, 0)
    Vector3 vec2{1};        // (1, 0, 0)
    Vector3 vec3{1, 2};     // (1, 2, 0)
    Vector3 vec4{1, 2, 3};  // (1, 2, 3)

    auto vec5 = vec2 + vec3;  // Using member operator+
    vec2 += vec3;             // Using member operator+=

    auto vec6 = 1 + vec4;  // Using global operator+
    // auto vec7 = 1 + vec4;          // Error if operator+ is a member function

    std::cout << "vec2: (" << vec2.x << ", " << vec2.y << ", " << vec2.z
              << ")\n";
    std::cout << "vec6: (" << vec6.x << ", " << vec6.y << ", " << vec6.z
              << ")\n";

    if (vec3 > vec2)
        std::cout << "vec3 is longer than vec2\n";
    else
        std::cout << "vec2 is longer or equal to vec3\n";

    return 0;
}
