#include <iostream>
#include <string>
#include <utility>
#include <new>

// Struct for a binary tree node
struct Tree {
    std::string str;
    Tree* left;
    Tree* right;
};

// Find function using exceptions
void fnd(Tree* p, const std::string& s) {
    if (s == p->str) throw p; // Found the value, throw the node
    if (p->left) fnd(p->left, s);
    if (p->right) fnd(p->right, s);
}

Tree* find(Tree* root, const std::string& s) {
    try {
        fnd(root, s);
    } catch (Tree* match) {
        return match; // Found node
    }
    return nullptr; // Not found
}

// Class with RAII mimicry
class MyVector {
    int* data;
    size_t size;
    int error_code;

public:
    MyVector(size_t n) : data(nullptr), size(n), error_code(0) {
        if (n == 0) {
            error_code = 1; // Invalid size
            return;
        }
        data = new (std::nothrow) int[n];
        if (!data) error_code = 2; // Memory allocation failure
    }

    ~MyVector() { delete[] data; }

    int invalid() const { return error_code; }

    int& operator[](size_t idx) { return data[idx]; }
};

// Function returning pair<Value, Error_code>
std::pair<int*, int> make_vector(size_t n) {
    if (n == 0) return {nullptr, 1}; // Error: invalid size
    int* data = new (std::nothrow) int[n];
    if (!data) return {nullptr, 2}; // Error: allocation failure
    return {data, 0}; // Success
}

// Main
int main() {
    // Binary tree search example
    Tree node3 = {"c", nullptr, nullptr};
    Tree node2 = {"b", nullptr, nullptr};
    Tree root = {"a", &node2, &node3};

    Tree* result = find(&root, "b");
    if (result) std::cout << "Found: " << result->str << '\n';

    // RAII mimicry example
    MyVector vec(0);
    if (vec.invalid()) {
        std::cerr << "Vector creation failed with error code " << vec.invalid() << '\n';
    }

    // Pair<Value, Error_code> example
    auto [data, error_code] = make_vector(10);
    if (error_code) {
        std::cerr << "Error creating vector: " << error_code << '\n';
    } else {
        delete[] data;
    }

    return 0;
}
