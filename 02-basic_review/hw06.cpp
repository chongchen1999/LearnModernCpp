#include <iostream>

// 使用 using 定义函数指针类型
using FuncPtr = int(*)(float, double);

// 接受函数指针为参数，返回 void 的函数
void processFunction(FuncPtr func) {
    if (func) {
        float f = 3.14f;
        double d = 2.718;
        int result = func(f, d); // 调用函数指针
        std::cout << "Function result: " << result << '\n';
    } else {
        std::cout << "Invalid function pointer!\n";
    }
}

// 示例函数，符合要求的签名
int exampleFunction(float a, double b) {
    return static_cast<int>(a + b); // 简单的操作：返回 float 和 double 的和的整数部分
}

int main() {
    // 将函数指针传递给 processFunction
    processFunction(exampleFunction);

    // 传递一个空指针测试
    processFunction(nullptr);

    return 0;
}
