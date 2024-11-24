#include <iostream>


struct A;
struct  A  {
    int x, y;
};
void f(A *a) {
    // A x;
    A *y = new A{0, 1};
}


int main() {

    return 0;
}