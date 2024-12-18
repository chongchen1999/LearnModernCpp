#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

// Explicit Qualification Example
class Employee {
public:
    virtual void print() const {
        cout << "Employee details\n";
    }
};

class Manager : public Employee {
public:
    void print() const override {
        Employee::print(); // Explicitly call base class print()
        cout << "\tlevel: Manager" << '\n';
    }
};

// Override Control Examples
struct B0 {
    virtual void g(double) {}
    virtual ~B0() = default;
};

struct D : B0 {
    // void g(int) override; // Uncommenting this will cause a compile-time error
};

// Using Base Members Example
struct Base {
    void f(int) { cout << "Base::f(int)\n"; }
};

struct Derived : Base {
    using Base::f;
    void f(double) { cout << "Derived::f(double)\n"; }
};

// Inheriting Constructors Example
template <class T>
struct Vector : std::vector<T> {
    using std::vector<T>::vector; // Inherit constructors
    T& operator[](size_t i) {
        check(i);
        return this->at(i);
    }
    void check(size_t i) {
        if (i >= this->size()) throw std::out_of_range("Index out of range");
    }
};

// Return Type Relaxation Example
class Expr {
public:
    virtual Expr* clone() = 0;
    virtual ~Expr() = default;
};

class Cond : public Expr {
public:
    Cond* clone() override { return new Cond(*this); }
};

// Main Function
int main() {
    // Explicit Qualification
    Manager mgr;
    mgr.print();

    // Using Base Members
    Derived d;
    d.f(42);       // Calls Base::f(int)
    d.f(3.14);     // Calls Derived::f(double)

    // Inheriting Constructors
    Vector<int> vec{1, 2, 3, 4, 5};
    try {
        cout << vec[2] << '\n'; // Access element
        cout << vec[10] << '\n'; // Out of range
    } catch (const std::exception& e) {
        cerr << e.what() << '\n';
    }

    // Return Type Relaxation
    Cond condObj;
    Expr* expr = condObj.clone();
    delete expr;

    return 0;
}
