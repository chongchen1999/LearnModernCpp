#include <iostream>

class Tiny {
    char v;
    void assign(int i) { 
        if (i & ~077) throw Bad_range(); 
        v = i; 
    }
public:
    class Bad_range { };

    Tiny(int i) { assign(i); }
    Tiny& operator=(int i) { assign(i); return *this; }
    operator int() const { return v; }
};

class MyUniquePtr {
    int* ptr;
public:
    explicit MyUniquePtr(int* p) : ptr(p) { }
    ~MyUniquePtr() { delete ptr; }
    explicit operator bool() const { return ptr != nullptr; }
};

class X {
public:
    X(int) {}
    X(const char*) {}
};

class Y {
public:
    Y(int) {}
};

class Z {
public:
    Z(X) {}
};

void f(X) { std::cout << "Called f(X)\n"; }
void f(Y) { std::cout << "Called f(Y)\n"; }
void g(Z) { std::cout << "Called g(Z)\n"; }

int main() {
    try {
        Tiny c1 = 2;
        Tiny c2 = 62;
        Tiny c3 = c2 - c1;
        std::cout << "c3: " << static_cast<int>(c3) << '\n';
    }
    catch (const Tiny::Bad_range&) {
        std::cerr << "Range error occurred.\n";
    }

    MyUniquePtr p1(new int(10));
    MyUniquePtr p2(nullptr);
    if (static_cast<bool>(p1)) std::cout << "Pointer is valid.\n";
    if (p1) std::cout << "Pointer is valid.\n";

    f(X{1});
    f(Y{1});
    g(X{"Doc"});
    g(Z{"Suzy"});

    return 0;
}
