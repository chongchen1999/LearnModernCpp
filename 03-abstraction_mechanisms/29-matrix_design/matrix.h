#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <array>

// Forward declarations
template<typename T, size_t N> class Matrix;
template<typename T, size_t N> class Matrix_ref;

// Matrix_slice class to handle N-dimensional slicing
template<size_t N>
class Matrix_slice {
public:
    Matrix_slice() = default;
    
    template<typename... Dims>
    Matrix_slice(Dims... dims) {
        static_assert(sizeof...(Dims) == N, "Dimension mismatch");
        init_extents(dims...);
    }

    size_t size() const { return total_size; }
    
    template<typename... Dims>
    size_t operator()(Dims... dims) const {
        static_assert(sizeof...(Dims) == N, "Dimension mismatch");
        std::array<size_t, N> indices{static_cast<size_t>(dims)...};
        return compute_index(indices);
    }

    std::array<size_t, N> extents;
    std::array<size_t, N> strides;
    size_t start{0};
    size_t total_size{1};

private:
    template<typename... Dims>
    void init_extents(Dims... dims) {
        std::array<size_t, N> arr{static_cast<size_t>(dims)...};
        extents = arr;
        compute_strides();
    }

    void compute_strides() {
        strides[N-1] = 1;
        for (int i = N-2; i >= 0; --i) {
            strides[i] = strides[i+1] * extents[i+1];
        }
        total_size = strides[0] * extents[0];
    }

    size_t compute_index(const std::array<size_t, N>& indices) const {
        size_t idx = start;
        for (size_t i = 0; i < N; ++i) {
            if (indices[i] >= extents[i]) throw std::out_of_range("Index out of bounds");
            idx += indices[i] * strides[i];
        }
        return idx;
    }
};

// Matrix class definition
template<typename T, size_t N>
class Matrix {
public:
    static constexpr size_t order = N;
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    Matrix() = default;
    Matrix(Matrix&&) = default;
    Matrix& operator=(Matrix&&) = default;
    Matrix(Matrix const&) = default;
    Matrix& operator=(Matrix const&) = default;
    ~Matrix() = default;

    template<typename U>
    Matrix(const Matrix_ref<U,N>&);

    template<typename U>
    Matrix& operator=(const Matrix_ref<U,N>&);

    template<typename... Exts>
    explicit Matrix(Exts... exts) : desc(exts...), elems(desc.size()) {}

    size_t extent(size_t n) const { return desc.extents[n]; }
    size_t size() const { return elems.size(); }
    const Matrix_slice<N>& descriptor() const { return desc; }
    
    T* data() { return elems.data(); }
    const T* data() const { return elems.data(); }

    // Subscripting operators
    template<typename... Dims>
    T& operator()(Dims... dims) {
        return elems[desc(dims...)];
    }

    template<typename... Dims>
    const T& operator()(Dims... dims) const {
        return elems[desc(dims...)];
    }

    // Iterator support
    iterator begin() { return elems.begin(); }
    iterator end() { return elems.end(); }
    const_iterator begin() const { return elems.begin(); }
    const_iterator end() const { return elems.end(); }
    const_iterator cbegin() const { return elems.cbegin(); }
    const_iterator cend() const { return elems.cend(); }

private:
    Matrix_slice<N> desc;
    std::vector<T> elems;
};

#endif // MATRIX_H