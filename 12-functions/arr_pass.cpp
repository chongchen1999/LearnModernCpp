#include <iostream>

template<class T, int N>
void f3(T (&&arr)[N]) {
    std::cout << "Unified array overload: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << std::endl;
}

int main() {
    int arr[] = {5, 6, 7, 8};
    
    // Both lvalue and rvalue calls work
    f3(arr);
    f3({5, 6, 7, 8});
    
    return 0;
}