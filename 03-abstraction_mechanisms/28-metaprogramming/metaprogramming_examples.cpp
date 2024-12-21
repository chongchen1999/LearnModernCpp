// metaprogramming_examples.cpp
#include <iostream>
#include <type_traits>
#include <cstring>

// Type function example: Multi-argument type function
template<typename T, int N>
struct Array_type {
    using type = T;
    static const int dim;
};

template<typename T, int N>
const int Array_type<T, N>::dim = N;

// Type selection example
template<typename T>
struct On_heap {
    On_heap() : p(new T) {}
    ~On_heap() { delete p; }

    T& operator*() { return *p; }
    T* operator->() { return p; }

private:
    T* p;
};

template<typename T>
struct Scoped {
    T& operator*() { return x; }
    T* operator->() { return &x; }

private:
    T x;
};

constexpr int on_stack_max = sizeof(std::string);

template<typename T>
struct Obj_holder {
    using type = typename std::conditional<(sizeof(T) <= on_stack_max), Scoped<T>, On_heap<T>>::type;
};

template<typename T>
using Holder = typename Obj_holder<T>::type;

// Type predicate example
template<typename T>
void copy(T* p, const T* q, int n) {
    if (std::is_standard_layout<T>::value && std::is_trivial<T>::value)
        std::memcpy(p, q, n);
    else
        for (int i = 0; i != n; ++i)
            p[i] = q[i];
}

// Iterator traits example
template<typename Iterator>
struct iterator_traits {
    using value_type = typename Iterator::value_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
};

int main() {
    // Array_type example
    using Array = Array_type<int, 3>;
    Array::type x = 42;
    constexpr int dim = Array::dim;
    std::cout << "Array type: " << x << ", dimensions: " << dim << "\n";

    // Holder example
    Holder<int> h;
    *h = 10;

    // Type predicate example
    int arr[5];
    copy(arr, arr, 5);

    return 0;
}
