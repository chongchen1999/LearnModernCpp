#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int i = 7.9;                  // Implicit, might truncate
    int j {static_cast<int>(7.9)}; // Explicit using braces ({})

    double d1 = double{2};        // OK, no precision loss
    // int k {7.9};                  // Error, narrowing conversion not allowed

    cout << "i: " << i << ", j: " << j << ", d1: " << d1 << endl;
    return 0;
}
