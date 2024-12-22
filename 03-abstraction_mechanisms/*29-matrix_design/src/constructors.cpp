#include "matrix.h"

template <typename T, size_t N>
template <typename... Exts>
Matrix<T, N>::Matrix(Exts... exts)
    : desc{exts...},              // Initialize descriptor with extents
      elems(desc.size)            // Allocate memory for elements
{
    // Elements are default-initialized
}

template <typename T, size_t N>
Matrix<T, N>::Matrix(Matrix_initializer<T, N> init) {
    Matrix_impl::derive_extents(init, desc.extents);  // Deduce extents from initializer list
    elems.reserve(desc.size);                        // Reserve space for elements
    Matrix_impl::insert_flat(init, elems);           // Initialize elements
    assert(elems.size() == desc.size);               // Ensure size consistency
}

