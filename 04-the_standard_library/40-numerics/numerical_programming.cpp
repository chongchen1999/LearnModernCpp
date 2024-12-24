#include <complex>
#include <valarray>
#include <iostream>
#include <cmath>

int main() {
    // Complex numbers
    std::complex<double> z1(1.0, 2.0);
    std::complex<double> z2(3.0, 4.0);

    std::complex<double> sum = z1 + z2;
    std::cout << "Sum of complex numbers: (" << sum.real() << ", " << sum.imag() << ")" << std::endl;

    std::complex<double> product = z1 * z2;
    std::cout << "Product of complex numbers: (" << product.real() << ", " << product.imag() << ")" << std::endl;

    // valarray constructors and assignments
    std::valarray<int> v1(10);
    std::valarray<int> v2(5, 10);
    int arr[] = {1, 2, 3, 4, 5};
    std::valarray<int> v3(arr, 5);

    std::valarray<int> v4 = v3;
    v1 = v2;
    v1 = 5;

    // valarray subscripting
    char char_arr[] = "abcdefghijklmnop";
    std::valarray<char> char_v0(char_arr, 16);

    std::valarray<char> char_v1 = char_v0[std::slice(2, 5, 3)];
    std::cout << "Slice result of valarray: ";
    for (char c : char_v1) {
        std::cout << c;
    }
    std::cout << std::endl;

    bool mask[] = {false, false, true, true, false, true};
    std::valarray<char> char_v2 = char_v0[std::valarray<bool>(mask, 6)];
    std::cout << "Mask result of valarray: ";
    for (char c : char_v2) {
        std::cout << c;
    }
    std::cout << std::endl;

    // valarray operations
    std::valarray<double> v5(5, 2.0);
    std::valarray<double> v6(5, 3.0);

    std::valarray<double> sum_v = v5 + v6;
    std::valarray<double> product_v = v5 * v6;
    std::valarray<double> cos_values = std::cos(v5);

    std::cout << "Sum of valarrays: ";
    for (double d : sum_v) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    std::cout << "Product of valarrays: ";
    for (double d : product_v) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    std::cout << "Cos values of valarray: ";
    for (double d : cos_values) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    // Slices
    int slice_arr[] = {0, 1, 2, 3, 10, 11, 12, 13, 20, 21, 22, 23};
    std::valarray<int> slice_val(slice_arr, 12);

    std::valarray<int> row_slice = slice_val[std::slice(0, 4, 1)];
    std::valarray<int> col_slice = slice_val[std::slice(0, 3, 4)];

    std::cout << "Row slice result: ";
    for (int i : row_slice) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Col slice result: ";
    for (int i : col_slice) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Generalized Slices
    std::valarray<size_t> lengths{2, 3};
    std::valarray<size_t> strides{3, 1};
    std::gslice g(0, lengths, strides);

    std::valarray<int> subarray_gslice = slice_val[g];

    std::cout << "Subarray from gslice: ";
    for (int i : subarray_gslice) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}