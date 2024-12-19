#include <iostream>
#include <string>

// Friend Function Example: Matrix and Vector
constexpr int rc_max = 4;

class Matrix;

class Vector {
    float v[rc_max];
public:
    Vector() { for (int i = 0; i < rc_max; ++i) v[i] = 0; }
    float& operator[](int index) { return v[index]; }
    float operator[](int index) const { return v[index]; }
    friend Vector operator*(const Matrix&, const Vector&);
};

class Matrix {
    Vector v[rc_max];
public:
    Matrix() { for (int i = 0; i < rc_max; ++i) for (int j = 0; j < rc_max; ++j) v[i][j] = i + j; }
    const Vector& operator[](int index) const { return v[index]; }
    friend Vector operator*(const Matrix&, const Vector&);
};

Vector operator*(const Matrix& m, const Vector& v) {
    Vector r;
    for (int i = 0; i < rc_max; ++i) {
        r[i] = 0;
        for (int j = 0; j < rc_max; ++j) {
            r[i] += m[i][j] * v[j];
        }
    }
    return r;
}

// Friend Class Example
class List;

class ListIterator {
public:
    int next();
};

class List {
    friend class ListIterator;
private:
    int items[10];
};

// Friend Template Example
template <typename T>
class X {
    friend T;
    int value;
};

int main() {
    // Test: Matrix and Vector
    Matrix m;
    Vector v;
    for (int i = 0; i < rc_max; ++i) {
        v[i] = i + 1;
    }
    Vector result = m * v;
    for (int i = 0; i < rc_max; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
