#include <cstdio>
#include <initializer_list>
#include <iostream>
void f(int d) {
    const auto max = d + 7;
    printf("%d\n", max);
}

int main() {
    auto x3 = {1,2,3};
    std::cout << typeid(x3).name() << std::endl;
    return 0;
}