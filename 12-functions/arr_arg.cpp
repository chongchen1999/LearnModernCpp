#include <iostream>
#include <vector>
#include <array>

// Example 1: Passing Arrays to Functions
int strlen(const char* str) {
    int length = 0;
    while (*str++) ++length;
    return length;
}

void example1() {
    char v[] = "Annemarie";
    int i = strlen(v);       // Array decays to char*
    int j = strlen("Nicholas");
    std::cout << "Length of 'Annemarie': " << i << ", Length of 'Nicholas': " << j << '\n';
}

// Example 2: Handling Array Size
void compute1(int* vec_ptr, int vec_size) {
    for (int i = 0; i < vec_size; ++i) {
        std::cout << vec_ptr[i] << " ";
    }
    std::cout << '\n';
}

void example2() {
    int arr[] = {1, 2, 3, 4, 5};
    compute1(arr, 5);
}

// Example 3: Reference to Array
void f(int(&r)[4]) {
    for (int i : r) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}

void example3() {
    int a1[] = {1, 2, 3, 4};
    f(a1); // OK
    // int a2[] = {1, 2}; 
    // f(a2); // Error: wrong number of elements
}

// Example 4: Templates with Array References
template<class T, int N>
void f(T(&r)[N]) {
    for (const auto& elem : r) {
        std::cout << elem << " ";
    }
    std::cout << "\nArray size: " << N << '\n';
}

void example4() {
    int a1[10] = {0};
    double a2[20] = {0.0};
    f(a1); // T is int, N is 10
    f(a2); // T is double, N is 100
}

// Example 5: Multidimensional Arrays with Pointers
void example5() {
    const char* day[] = {
        "mon", "tue", "wed", "thu", "fri", "sat", "sun"
    };
    for (const char* d : day) {
        std::cout << d << " ";
    }
    std::cout << '\n';
}

int main() {
    std::cout << "Example 1:\n";
    example1();
    
    std::cout << "\nExample 2:\n";
    example2();
    
    std::cout << "\nExample 3:\n";
    example3();
    
    std::cout << "\nExample 4:\n";
    example4();
    
    std::cout << "\nExample 5:\n";
    example5();
    
    return 0;
}
