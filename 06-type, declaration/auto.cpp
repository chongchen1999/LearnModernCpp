#include <cstdio>
#include <initializer_list>
#include <iostream>
void f(int d) {
    const auto max = d + 7;
    printf("%d\n", max);
}

void f(const int &a, const int &b) {

}

int main() {
    const auto &x3 = {1,2,3};
    const int x = 10;
    const auto y = x;
    f(x, y);
    std::cout << typeid(x3).name() << std::endl;
    return 0;
}