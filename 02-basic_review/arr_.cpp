#include <stdio.h>

void example(int n) {
    int arr[n];  // VLA: the size of the array is determined at runtime
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    example(5);  // Creates an array of size 5
    example(8);  // Creates an array of size 8

    int* arr = new int[3]{1, 2, 3};  // Dynamically allocated array
    for (int i = 0; i < 3; i++) {
        printf("%d ", arr[i]);
    }
    delete[] arr;  // Free the memory

    return 0;
}
