#include <iostream>

// Example 1: Array and Pointer Declarations
void example1() {
    int a[][3] = { {1, 2, 3}, {4, 5, 6} };
    int (*b)[3] = a; // Valid: 'a' decays to 'int (*)[3]'.
    // int **c = a;    // Invalid: 'a' decays to 'int (*)[3]', not 'int**'.
    // int **d = b;    // Invalid: 'b' is 'int (*)[3]', not 'int**'.

    std::cout << "example1: b[1][1] = " << b[1][1] << '\n'; // Access element via pointer
}

// Example 2: Function Overloads with Arrays and Pointers
void Func(int (&a)[3]) { // Function taking reference to array of size 3
    std::cout << "Func: Received array of size 3\n";
}

void Func2(int a[3]) { // Function taking pointer to array element
    std::cout << "Func2: Received array (decayed to pointer)\n";
}

void example2() {
    int a[] = {1, 2, 3};       // Array of size 3
    int b[] = {4, 5, 6, 7};    // Array of size 4

    Func(a);    // Valid: 'a' is exactly an array of size 3
    Func2(a);   // Valid: 'a' decays to pointer to int
    // Func(b); // Invalid: 'b' is array of size 4, not size 3
    Func2(b);   // Valid: 'b' decays to pointer to int
}

int main() {
    std::cout << "Running example1:\n";
    example1();

    std::cout << "\nRunning example2:\n";
    example2();

    return 0;
}
