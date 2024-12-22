#pragma once
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>

template <typename T, size_t N>
class Matrix {
public:
    // Types and constants
    static constexpr size_t order = N;
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    // Constructors and assignment operators
    Matrix() = default;
    Matrix(Matrix&&) = default;                         // Move constructor
    Matrix& operator=(Matrix&&) = default;              // Move assignment
    Matrix(const Matrix&) = default;                    // Copy constructor
    Matrix& operator=(const Matrix&) = default;         // Copy assignment
    ~Matrix() = default;                                // Destructor

    template <typename U>
    Matrix(const Matrix_ref<U, N>&);                    // Construct from Matrix_ref

    template <typename U>
    Matrix& operator=(const Matrix_ref<U, N>&);         // Assign from Matrix_ref

    template <typename... Exts>
    explicit Matrix(Exts... exts);                      // Specify the extents

    Matrix(Matrix_initializer<T, N>);                   // Initialize from list
    Matrix& operator=(Matrix_initializer<T, N>);        // Assign from list

    template <typename U>
    Matrix(std::initializer_list<U>) = delete;          // Disallow `{}` for non-elements

    template <typename U>
    Matrix& operator=(std::initializer_list<U>) = delete;

    // Accessor methods
    static constexpr size_t order() { return N; }       // Number of dimensions
    size_t extent(size_t n) const { return desc.extents[n]; } // Elements in nth dimension
    size_t size() const { return elems.size(); }        // Total number of elements

    const Matrix_slice<N>& descriptor() const { return desc; } // Slice defining subscripting
    T* data() { return elems.data(); }                  // Access raw element array
    const T* data() const { return elems.data(); }      // Access raw element array (const)

private:
    Matrix_slice<N> desc;  // Slice defining dimensions
    std::vector<T> elems;  // Storage for elements
};
