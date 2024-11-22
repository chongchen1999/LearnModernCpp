#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int N = 10;
int main() {
    const char *str = "123456";
    const char *str2 = "123456";

    std::cout << *str << std::endl;
    std::cout << *str2 << std::endl;

    std::cout << static_cast<const void *>(str) << std::endl;
    std::cout << static_cast<const void *>(str2) << std::endl;
    std::cout << &N <<std::endl;

    printf("%s\n", str);
    printf("%ld\n", strlen(str));
    return 0;
}