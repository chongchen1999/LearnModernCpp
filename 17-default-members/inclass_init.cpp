#include <iostream>
#include <string>

// Global variables
int count = 0;
int count2 = 0;

// Helper function
int f(int i) { return i + count; }

// Class with in-class initializers and examples
class A {
public:
    // Constructors
    A() {}                        // Default constructor
    A(int a_val) : a{a_val} {}    // Overrides in-class initializer for 'a'
    A(int x, int d) : b{g(d)} {}         // Overrides in-class initializer for 'b'

private:
    int a {7};                    // In-class initializer
    int b {5};                    // In-class initializer
    std::string algorithm {"MD5"};    // Default hash function
    std::string state {"Constructor run"}; // Lifecycle state

    // Simulated function for example
    int g(int x) { return x * 2; }
};

struct S {
    int m1 {count2};    // Initialized with global variable 'count2'
    int m2 {f(m1)};     // Depends on 'm1' and global function 'f'

    S() { ++count2; }   // Constructor increments global variable 'count2'
};

int main() {
    S s1;  // {m1=0, m2=0}
    std::cout << "s1: m1=" << s1.m1 << ", m2=" << s1.m2 << "\n";

    ++count;  // Increment global 'count'

    S s2;  // {m1=1, m2=2}
    std::cout << "s2: m1=" << s2.m1 << ", m2=" << s2.m2 << "\n";

    return 0;
}
