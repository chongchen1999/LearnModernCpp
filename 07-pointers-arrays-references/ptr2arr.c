#include <stdio.h>

void test1() {
    int arr[] = {1, 2, 3};
    int *ptr = arr; // ok

    // int arr2[];
    int *q;

    printf("%ld\n", sizeof(arr));
    printf("%ld\n", sizeof(ptr));
}

void test2() {
    int n;
    scanf("%d", &n);
    int arr2[n];
    printf("%ld\n", sizeof(arr2));
}

void test3() {
    int x, y, n;
    scanf("%d", &n);
    printf("%p\n", &x);
    printf("%p\n", &y);
    printf("%p\n", &n);

    int arr[n];
    printf("%p\n", arr);
    printf("%p\n", &arr);

    printf("%p\n", &arr[0]);
    printf("%p\n", &arr[1]);
    printf("%p\n", &arr[2]);

    printf("%ld\n", sizeof(arr));
}

int main() {
    test3();
    return 0;
}