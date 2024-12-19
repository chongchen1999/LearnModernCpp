#include <iostream>

struct X {
    void f() { std::cout << "Member function f() called\n"; }
    int m;

    // Access member directly inside the class
    void accessMember() { m = 1; } // Equivalent to "this->m = 1;"
};

void user(X x, X* px) {
    // m = 1;  // Error: no m in scope
    x.m = 1;    // OK: x is an object of class X
    // x->m = 1; // Error: x is not a pointer
    px->m = 1;  // OK: px is a pointer to an object of X
    // px.m = 1; // Error: px is a pointer, not an object
}

struct S {
    int m;                  // Non-static member
    int f();                // Non-static member function
    static int sm;          // Static member
};

// Defining a member function outside the class
int S::f() { return m; }    // Accesses non-static member m of an S object
int S::sm = 7;              // Initialize static member sm

int main() {
    X x;
    X* px = &x;

    user(x, px);            // Demonstrating . and -> operators

    S s;
    int (S::*pmf)() = &S::f; // Pointer to member function
    std::cout << "Static member sm: " << S::sm << '\n';

    return 0;
}
