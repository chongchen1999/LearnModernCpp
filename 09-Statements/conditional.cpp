#include <iostream>
#include <string>
using namespace std;

double prim(bool flag) {
    return flag ? 2.5 : 0.0; // Example function: returns a value based on a condition
}

void conditionalExamples() {
    cout << "Demonstrating conditional statements with variable declarations\n";

    // 1. Correct: Declare and initialize a variable inside a condition
    if (double d = prim(true)) { // d is declared and initialized here
        cout << "Condition met. Value of d: " << d << endl;
    } else {
        cout << "Condition not met. d is out of scope here." << endl;
    }
    // d is out of scope now

    // 2. Incorrect: Uninitialized variable before a condition
    double uninitialized;
    // cout << "Value of uninitialized variable: " << uninitialized << endl; // Uncomment for undefined behavior
    if ((uninitialized = prim(false))) { // Assigning value inside the condition
        cout << "This branch won't execute since uninitialized = 0." << endl;
    }

    // 3. Correct: Declare multiple variables in separate conditions
    if (int x = 5) { // Declare and initialize x
        cout << "x is initialized to: " << x << endl;
    }
    // x is out of scope here

    if (string s{}; !s.empty()) { // Declare and initialize s
        cout << "String s: " << s << endl;
    } else {
        s = "Empty string";
        cout << s << endl;
    }
    // s is out of scope here

    // 4. Incorrect: Declare multiple variables in a single condition (Error)
    // if (int x = 5, y = 10) { // Uncomment this for compilation error
    //     cout << x << ", " << y << endl;
    // }

    // 5. Correct: Avoid reusing variables outside their intended scope
    if (int a = 10) { // Declare and initialize a
        cout << "a inside if: " << a << endl;
    }
    // cout << "a outside if: " << a << endl; // Uncomment for scope error

    // 6. Reusing a variable outside (not best practice)
    int b = 15;
    if (b > 10) {
        cout << "b is used in the if-statement: " << b << endl;
    }
    b = 20; // Reassigned after its intended scope
    cout << "b reused later: " << b << endl;
}

int main() {
    conditionalExamples();
    return 0;
}
