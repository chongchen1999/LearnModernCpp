#include <iostream>
#include <stdexcept>

template<typename T>
class Ptr {
    T* ptr;       // Pointer to the current object
    T* data;     // Pointer to the beginning of the array
    int sz;       // Size of the array

public:
    // Constructor for binding to a fixed-size array
    template<int N>
    Ptr(T* p, T(&a)[N])
        : ptr(p), data(a), sz(N) {}

    // Constructor for general array binding
    Ptr(T* p, T* a, int s)
        : ptr(p), data(a), sz(s) {}

    // Constructor for single object
    Ptr(T* p)
        : ptr(p), data(nullptr), sz(0) {}

    // Prefix increment
    Ptr& operator++() {
        if (!data || ptr + 1 >= data + sz)
            throw std::out_of_range("Pointer out of range on increment");
        ++ptr;
        return *this;
    }

    // Postfix increment
    Ptr operator++(int) {
        if (!data || ptr + 1 >= data + sz)
            throw std::out_of_range("Pointer out of range on increment");
        Ptr old = *this;
        ++ptr;
        return old;
    }

    // Prefix decrement
    Ptr& operator--() {
        if (!data || ptr - 1 < data)
            throw std::out_of_range("Pointer out of range on decrement");
        --ptr;
        return *this;
    }

    // Postfix decrement
    Ptr operator--(int) {
        if (!data || ptr - 1 < data)
            throw std::out_of_range("Pointer out of range on decrement");
        Ptr old = *this;
        --ptr;
        return old;
    }

    // Dereference operator
    T& operator*() {
        if (!data || ptr < data || ptr >= data + sz)
            throw std::out_of_range("Pointer out of range on dereference");
        return *ptr;
    }
};

// Test function
void test_ptr() {
    int arr[5] = {1, 2, 3, 4, 5};
    Ptr<int> p(&arr[0], arr);

    try {
        std::cout << *p << "\n";  // Output: 1
        ++p;
        std::cout << *p << "\n";  // Output: 2
        p++;
        std::cout << *p << "\n";  // Output: 3
        --p;
        std::cout << *p << "\n";  // Output: 2
        p--;
        std::cout << *p << "\n";  // Output: 1
        p--;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << "\n";
    }
}

int main() {
    test_ptr();
    return 0;
}
