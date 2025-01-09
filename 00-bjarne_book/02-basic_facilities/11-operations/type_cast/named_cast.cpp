#include <iostream>
using namespace std;

int main() {
    long x = 0x7ffef98dbd5c;
    int* ptr = reinterpret_cast<int*>(x); // Treat integer as pointer
    cout << "Pointer: " << ptr << endl; // Pointer: 0x7ffef98dbd5c
    // cout << "Value: " << *ptr << endl;
    return 0;
}
