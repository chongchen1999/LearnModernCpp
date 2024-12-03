#include <iostream>
#include <new> // For nothrow

int main() {
    const size_t LARGE_SIZE = 2e9;

    // Allocate memory with nothrow
    int* arr = new (std::nothrow) int[LARGE_SIZE];

    if (!arr) {
        std::cout << "Memory allocation failed!\n";
    } else {
        std::cout << "Memory allocated successfully!\n";
        std::cout << sizeof(arr) << std::endl;
        // Use the array
        arr[0] = 42;
        std::cout << "First element: " << arr[0] << '\n';

        // Deallocate memory
        delete[] arr;
    }

    return 0;
}
