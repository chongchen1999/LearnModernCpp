#include <algorithm>
#include <iostream>
#include <vector>

void fillFibonacci(std::vector<int>& v) {
    std::ranges::generate(v, [a = 0, b = 1]() mutable {
        int next = a;
        a = b;
        b = next + b;
        return next;
    });
}

int main() {
    std::vector<int> fib(10);  // 假设我们要生成前10个斐波那契数
    fillFibonacci(fib);

    for (const auto& num : fib) {
        std::cout << num << " ";
    }

    return 0;
}