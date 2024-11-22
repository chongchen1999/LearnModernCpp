### 数组和指针的区别

int arr[] = {1, 2, 3};
int *ptr = arr; // ok

int arr2[] = ptr; // error

sizeof(arr); // 12
sizoef(ptr); // 8 in 64-bit machine
sizeof((void *)arr); // 8

int *q; //ok, declare a pointer
int *arr[]; //error

对于数组，如果是动态分配，则通过metadata确定数组大小

### What Happens During Array Decay?
When you pass an array to a function, it decays into a pointer, losing the information about its size. For example:
```c
void myFunction(int arr[]) {
    // sizeof(arr) gives the size of a pointer, not the array
    printf("Size of arr in function: %zu\n", sizeof(arr));
}

int main() {
    int arr[] = {1, 2, 3};
    printf("Size of arr in main: %zu\n", sizeof(arr));
    myFunction(arr);
    return 0;
}
```
Output:
```
Size of arr in main: 12
Size of arr in function: 8 // or 4, depending on pointer size
```