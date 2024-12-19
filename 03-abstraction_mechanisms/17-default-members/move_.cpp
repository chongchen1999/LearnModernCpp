#include <iostream>
#include <array>
#include <utility> // For std::move and std::swap

template<class T>
class Matrix {
    std::array<int, 2> dim; // Matrix dimensions
    T* elem;               // Pointer to elements

public:
    // Constructor
    Matrix(int d1, int d2) : dim{d1, d2}, elem{new T[d1 * d2]} {}

    // Destructor
    ~Matrix() { delete[] elem; }

    // Copy Constructor
    Matrix(const Matrix& a) : dim{a.dim}, elem{new T[a.size()]} {
        for (int i = 0; i < size(); ++i) elem[i] = a.elem[i];
    }

    // Copy Assignment
    Matrix& operator=(const Matrix& a) {
        if (this == &a) return *this; // Self-assignment check
        T* p = new T[a.size()];
        for (int i = 0; i < a.size(); ++i) p[i] = a.elem[i];
        delete[] elem;
        elem = p;
        dim = a.dim;
        return *this;
    }

    // Move Constructor
    Matrix(Matrix&& a) noexcept : dim{a.dim}, elem{a.elem} {
        a.dim = {0, 0};
        a.elem = nullptr;
    }

    // Move Assignment
    Matrix& operator=(Matrix&& a) noexcept {
        if (this == &a) return *this; // Self-assignment check
        std::swap(dim, a.dim);
        std::swap(elem, a.elem);
        return *this;
    }

    int size() const { return dim[0] * dim[1]; }

    // Element access
    T& operator()(int i, int j) { return elem[i * dim[1] + j]; }
    const T& operator()(int i, int j) const { return elem[i * dim[1] + j]; }

    // Friend operator for addition
    friend Matrix operator+(const Matrix& a, const Matrix& b) {
        if (a.dim != b.dim) throw std::runtime_error("Matrix dimensions must match");
        Matrix res(a.dim[0], a.dim[1]);
        for (int i = 0; i < a.size(); ++i) {
            res.elem[i] = a.elem[i] + b.elem[i];
        }
        return res; // Move constructor is used here
    }
};

// Swap function using move
template<class T>
void swap(Matrix<T>& a, Matrix<T>& b) {
    Matrix<T> tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

// Test the Matrix class
int main() {
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);

    m1(0, 0) = 1; m1(0, 1) = 2; m1(1, 0) = 3; m1(1, 1) = 4;
    m2(0, 0) = 5; m2(0, 1) = 6; m2(1, 0) = 7; m2(1, 1) = 8;

    std::cout << "Before swap:\n";
    std::cout << "m1(0,0): " << m1(0, 0) << " m2(0,0): " << m2(0, 0) << '\n';

    swap(m1, m2);

    std::cout << "After swap:\n";
    std::cout << "m1(0,0): " << m1(0, 0) << " m2(0,0): " << m2(0, 0) << '\n';

    Matrix<int> m3 = m1 + m2;
    std::cout << "m3(0,0): " << m3(0, 0) << '\n';

    return 0;
}
