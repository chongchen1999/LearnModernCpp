#include "matrix.h"
#include <iostream>
#include <cassert>

// Helper function to print a 2D matrix
template<typename T>
void print_matrix(const Matrix<T, 2>& m) {
    for (size_t i = 0; i < m.extent(0); ++i) {
        for (size_t j = 0; j < m.extent(1); ++j) {
            std::cout << m(i,j) << " ";
        }
        std::cout << "\n";
    }
}

void test_matrix_construction() {
    std::cout << "Testing matrix construction...\n";
    
    // Test basic construction
    Matrix<int, 2> m1(3, 4);  // 3x4 matrix
    assert(m1.extent(0) == 3);
    assert(m1.extent(1) == 4);
    assert(m1.size() == 12);
    
    // Fill matrix with values
    int val = 0;
    for (size_t i = 0; i < m1.extent(0); ++i) {
        for (size_t j = 0; j < m1.extent(1); ++j) {
            m1(i,j) = val++;
        }
    }
    
    std::cout << "Matrix m1:\n";
    print_matrix(m1);
    
    // Test copy construction
    Matrix<int, 2> m2 = m1;
    std::cout << "\nCopied matrix m2:\n";
    print_matrix(m2);
    
    // Test element access
    assert(m2(1,1) == m1(1,1));
    
    // Modify m2 and verify m1 is unchanged
    m2(1,1) = 99;
    assert(m2(1,1) != m1(1,1));
    
    std::cout << "\nModified m2:\n";
    print_matrix(m2);
}

void test_matrix_operations() {
    std::cout << "\nTesting matrix operations...\n";
    
    // Create a 2x3 matrix
    Matrix<double, 2> m(2, 3);
    
    // Fill with values
    m(0,0) = 1.0; m(0,1) = 2.0; m(0,2) = 3.0;
    m(1,0) = 4.0; m(1,1) = 5.0; m(1,2) = 6.0;
    
    std::cout << "Matrix m:\n";
    print_matrix(m);
    
    // Test iterator
    std::cout << "\nIterating through matrix:\n";
    for (const auto& elem : m) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    
    // Test const access
    const Matrix<double, 2>& cm = m;
    assert(cm(0,0) == 1.0);
    
    // Test out of bounds access
    try {
        m(2,0);  // This should throw
        assert(false);  // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "\nCaught expected out of bounds exception\n";
    }
}

int main() {
    try {
        test_matrix_construction();
        test_matrix_operations();
        
        // Test 3D matrix
        Matrix<int, 3> m3d(2, 3, 4);
        assert(m3d.size() == 24);
        std::cout << "\nCreated 3D matrix with size: " << m3d.size() << "\n";
        
        std::cout << "\nAll tests passed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}