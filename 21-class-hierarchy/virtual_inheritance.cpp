#include <iostream>
using namespace std;

// Base class
class Base {
public:
    void display() {
        cout << "Base class method" << endl;
    }
};

// Class A virtually inherits from Base
class A : virtual public Base {
};

// Class B virtually inherits from Base
class B : virtual public Base {
};

// Class C inherits from both A and B
class C : public A, public B {
};

int main() {
    C obj;
    obj.display(); // No ambiguity due to virtual inheritance
    return 0;
}
