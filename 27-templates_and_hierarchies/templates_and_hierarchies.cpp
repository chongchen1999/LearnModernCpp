#include <iostream>

// Generic template class
template<typename X>
class Ct {
    X mem;  // Generic member
public:
    X f() { return mem; }
    int g() { return 42; }
    void h(X value) { mem = value; }
};

// Specialization for type A
class A {
    int value;
public:
    A(int val = 0) : value(val) {}
    int getValue() const { return value; }
};

template<>
class Ct<A> {
    A* mem;  // Different representation
public:
    Ct() : mem(nullptr) {}
    A f() { return *mem; }
    int g() { return 42; }
    void h(A value) { mem = new A(value); }
    void k(int extra) { std::cout << "Extra: " << extra << "\n"; }
};

// Base class with virtual functions
class X {
    int data;
public:
    X(int d = 0) : data(d) {}
    int getData() const { return data; }
};

class Cx {
    X mem;  // Base member
public:
    virtual X& f() { return mem; }
    virtual int g() { return 42; }
    virtual void h(X&) {}
    virtual ~Cx() {}
};

// Derived class DA
class DA : public Cx {
    X data;
public:
    DA(int val = 0) : data(val) {}
    X& f() override { return data; }
    int g() override { return 100; }
    void h(X& x) override { data = x; }
};

// Derived class DB
class DB : public Cx {
    X data;
    DB* p;  // Extended representation
public:
    DB(int val = 0) : data(val), p(nullptr) {}
    X& f() override { return data; }
    int g() override { return 200; }
    void h(X& x) override { data = x; }
    void k(int extra) { std::cout << "Extra functionality: " << extra << "\n"; }
};

int main() {
    // Using templates
    Ct<int> cti;
    cti.h(10);
    std::cout << "Template Ct<int>: " << cti.f() << "\n";

    Ct<A> cta;
    cta.h(A(42));
    std::cout << "Template Ct<A>: " << cta.f().getValue() << "\n";
    cta.k(99);

    // Using class hierarchies
    DA da(10);
    DB db(20);
    Cx& cxa = da;
    Cx& cxb = db;

    std::cout << "Hierarchy DA g(): " << cxa.g() << "\n";
    std::cout << "Hierarchy DB g(): " << cxb.g() << "\n";

    return 0;
}
