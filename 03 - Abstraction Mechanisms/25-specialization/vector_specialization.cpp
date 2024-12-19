// vector_specialization.cpp
#include <iostream>
#include <utility>

// General template
template<typename T>
class Vector {
    T* v;
    int sz;
public:
    Vector() : v(nullptr), sz(0) {}
    explicit Vector(int size) : sz(size), v(new T[size]) {}
    T& elem(int i) { return v[i]; }
    T& operator[](int i) { return v[i]; }
    void swap(Vector& other) {
        std::swap(v, other.v);
        std::swap(sz, other.sz);
    }
    ~Vector() { delete[] v; }
};

// Complete specialization for void*
template<>
class Vector<void*> {
    void** p;
    int sz;
public:
    Vector() : p(nullptr), sz(0) {}
    explicit Vector(int size) : sz(size), p(new void*[size]) {}
    void*& operator[](int i) { return p[i]; }
    ~Vector() { delete[] p; }
};

// Partial specialization for all pointer types
template<typename T>
class Vector<T*> : private Vector<void*> {
public:
    using Base = Vector<void*>;
    Vector() {}
    explicit Vector(int size) : Base(size) {}
    T*& elem(int i) { return reinterpret_cast<T*&>(Base::operator[](i)); }
    T*& operator[](int i) { return reinterpret_cast<T*&>(Base::operator[](i)); }
};

// Example usage
int main() {
    Vector<int> vi(5);         // General template
    Vector<void*> vv(3);       // Complete specialization
    Vector<int*> vip(4);       // Partial specialization for pointers
    
    vi[0] = 42;
    int x = 7;
    vip[0] = &x;

    std::cout << "vi[0]: " << vi[0] << "\n";
    std::cout << "*vip[0]: " << *vip[0] << "\n";

    return 0;
}
