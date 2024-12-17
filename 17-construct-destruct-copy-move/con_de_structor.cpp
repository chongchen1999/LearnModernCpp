#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Tracer class to log construction and destruction
struct Tracer {
    string mess;

    Tracer(const string& s) : mess{s} {
        clog << mess; // Log construction
    }

    ~Tracer() {
        clog << "~" << mess; // Log destruction
    }
};

// Vector class with constructor and destructor
class Vector {
public:
    Vector(int s); // Constructor
    ~Vector();     // Destructor

private:
    double* elem; // Pointer to array
    int sz;       // Size of array
};

// Constructor definition
Vector::Vector(int s) {
    if (s < 0) throw invalid_argument{"Bad size"};
    sz = s;
    elem = new double[s];
    cout << "Vector of size " << sz << " constructed\n";
}

// Destructor definition
Vector::~Vector() {
    delete[] elem;
    cout << "Vector of size " << sz << " destructed\n";
}

// Base class with virtual destructor
class Shape {
public:
    virtual void draw() = 0;            // Pure virtual function
    virtual ~Shape() { cout << "Shape destructor\n"; } // Virtual destructor
};

class Circle : public Shape {
public:
    void draw() override { cout << "Drawing Circle\n"; }
    ~Circle() { cout << "Circle destructor\n"; }
};

// Function using Tracer for logging
void f(const vector<int>& v) {
    Tracer tr{"in f()\n"};
    for (auto x : v) {
        Tracer tr{string{"v loop "} + to_string(x) + '\n'};
    }
}

void user(Shape* p) {
    p->draw();  // Calls appropriate draw function
    delete p;   // Ensures correct destructor is called
}

int main() {
    cout << "Tracer Example:\n";
    f({2, 3, 5});

    cout << "\nVector Example:\n";
    try {
        Vector v(5);
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    cout << "\nVirtual Destructor Example:\n";
    Shape* shape = new Circle;
    user(shape);

    return 0;
}
