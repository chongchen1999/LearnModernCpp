#include <iostream>
#include <cmath>

constexpr int square(int x) {
    return x * x;
}

void my_test_function() {
    constexpr const char* p1 = "hello";
    constexpr const char* p2 = p1;    
    constexpr const char* p3 = p1 + 2;  
    constexpr char c = p1[1];           
    constexpr const void *p4 = p1;
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << c << std::endl;
    std::cout << p4 << std::endl;
}

int main() {
    // Compile-time evaluation
    constexpr int compile_time_result = square(5);  // 5 is a constant expression
    std::cout << "Compile-time result: " << compile_time_result << std::endl;

    // Runtime evaluation
    if (int a, b; std::cin >> a) {
        b = 100;
        int runtime_result = square(a);  // 'a' is a variable, so this is evaluated at runtime
        std::cout << "Runtime result: " << runtime_result << std::endl;
    }

    if (int x; x = sqrt(10)) {
        std::cout << square(sqrt(10)) << std::endl;
    }

    /*if (const char *str = "Hello, world!") {
        std:: cout << const_cast<void *>(static_cast<const void *>(str)) << std::endl;
    }*/

    return 0;
}
