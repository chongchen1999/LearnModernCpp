#include <iostream>
#include <array>
#include <memory>
#include <algorithm>
#include <stdexcept>

// Matrix Class Template
template<class T>
class Matrix {
    std::array<int, 2> dim;
    T* elem;

public:
    // Constructor
    Matrix(int d1, int d2) : dim{d1, d2}, elem{new T[d1 * d2]} {}

    // Destructor
    ~Matrix() { delete[] elem; }

    // Copy Constructor
    Matrix(const Matrix& m) 
        : dim{m.dim}, elem{new T[m.size()]} {
        std::uninitialized_copy(m.elem, m.elem + m.size(), elem);
    }

    // Copy Assignment (Copy-and-Swap)
    Matrix& operator=(const Matrix& m) {
        Matrix tmp{m};
        std::swap(tmp, *this);
        return *this;
    }

    // Move Constructor
    Matrix(Matrix&& m) noexcept 
        : dim{m.dim}, elem{m.elem} {
        m.elem = nullptr;
    }

    // Move Assignment
    Matrix& operator=(Matrix&& m) noexcept {
        delete[] elem;
        dim = m.dim;
        elem = m.elem;
        m.elem = nullptr;
        return *this;
    }

    int size() const { return dim[0] * dim[1]; }
};

// Base and Derived Classes to Demonstrate Slicing
struct Base {
    int b;
    Base(int x) : b{x} {}
    Base(const Base&) = delete;  // Prevent slicing
};

struct Derived : Base {
    int d;
    Derived(int x, int y) : Base{x}, d{y} {}
};

int main() {
    // Matrix Test
    Matrix<int> m1(2, 3);
    Matrix<int> m2 = m1;  // Copy
    Matrix<int> m3 = std::move(m1);  // Move

    // Inheritance Test (Prevent Slicing)
    Derived d{1, 2};
    // Base b = d;  // Error: copy constructor is deleted

    return 0;
}
