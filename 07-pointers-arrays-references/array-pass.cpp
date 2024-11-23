#include <cstdio>
void myFunction(int arr[5]) {
    // sizeof(arr) gives the size of a pointer, not the array
    printf("Size of arr in function: %ld\n", sizeof(arr));
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    printf("Size of arr in main: %ld\n", sizeof(arr));
    myFunction(arr);
    return 0;
}