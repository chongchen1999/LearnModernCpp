#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Section 17.6.3.1: Default Constructors
struct X {
    X(int val) { cout << "X initialized with " << val << endl; }
};

struct Y {
    string s;
    int n;
    Y(const string& str) : s{str} { cout << "Y initialized with string: " << s << endl; }
    Y() = default;  // Default constructor
};

// Section 17.6.3.2: Maintaining Invariants
struct Z {
    vector<int> elem;
    int my_favorite;
    int* largest;

    Z(vector<int> e, int fav, int* l) : elem{e}, my_favorite{fav}, largest{l} {}
};

// Section 17.6.3.3: Resource Management
template<class T>
class Handle {
    T* p;

public:
    Handle(T* pp) : p{pp} {}
    T& operator*() { return *p; }
    ~Handle() { delete p; cout << "Resource freed." << endl; }
};

// Section 17.6.3.4: Partially Specified Invariants
class Tic_tac_toe {
public:
    Tic_tac_toe() : pos(9) {}
    Tic_tac_toe(const Tic_tac_toe&) = default;
    Tic_tac_toe& operator=(const Tic_tac_toe&) = default;
    ~Tic_tac_toe() = default;

    enum State { empty, nought, cross };

private:
    vector<State> pos;
};

// Section 17.6.4: Deleted Functions
class Base {
public:
    Base& operator=(const Base&) = delete;
    Base(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(Base&&) = delete;
};

class Not_on_stack {
public:
    ~Not_on_stack() = delete;  // Cannot be destroyed
};

class Not_on_free_store {
public:
    void* operator new(size_t) = delete;  // Cannot allocate on heap
};

int main() {
    // Default Constructors
    X x1{10};
    Y y1{"Hello"};
    Y y2;

    // Maintaining Invariants
    Z z{{1, 2, 3}, 1, nullptr};

    // Resource Management
    Handle<int> h{new int{99}};
    cout << "Handle points to: " << *h << endl;

    // Partially Specified Invariants
    Tic_tac_toe game;

    // Deleted Functions
    // Base b1, b2;   // Copy and move operations are deleted

    // Not_on_free_store* p = new Not_on_free_store;  // Error: new is deleted
    return 0;
}
