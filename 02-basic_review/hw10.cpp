#include <iostream>

// 第一组测试
// void Test(int);  // 编译会报错
// int Test(int);   // 和上面冲突，无法区分

// 第二组测试
void Test(int) { std::cout << "Normal function called\n"; }

template <typename T>
T Test(int) {
    std::cout << "Template function called\n";
    return T();
}

int main() {
    Test(42);  // 如果 T = void，则会冲突。否则，调用普通函数。
    Test<int>(42);  // 强制调用模板函数。
    return 0;
}
