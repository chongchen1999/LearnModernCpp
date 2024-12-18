#include <iostream>
#include <vector>
#include <chrono>

class MyClassNoExcept {
private:
    int* data;

public:
    MyClassNoExcept(int value) {
        data = new int(value);
    }

    MyClassNoExcept(const MyClassNoExcept& other) {
        data = new int(*other.data);
    }

    MyClassNoExcept(MyClassNoExcept&& other) noexcept { // noexcept
        data = other.data;
        other.data = nullptr;
    }

    MyClassNoExcept& operator=(MyClassNoExcept&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    ~MyClassNoExcept() {
        delete data;
    }
};

class MyClassWithoutNoExcept {
private:
    int* data;

public:
    MyClassWithoutNoExcept(int value) {
        data = new int(value);
    }

    MyClassWithoutNoExcept(const MyClassWithoutNoExcept& other) {
        data = new int(*other.data);
    }

    MyClassWithoutNoExcept(MyClassWithoutNoExcept&& other) { // No noexcept
        data = other.data;
        other.data = nullptr;
    }

    MyClassWithoutNoExcept& operator=(MyClassWithoutNoExcept&& other) {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    ~MyClassWithoutNoExcept() {
        delete data;
    }
};

template <typename T>
void performanceTest(const std::string& testName) {
    constexpr size_t SIZE = 1000000; // Number of objects to test
    std::vector<T> vec;

    auto start = std::chrono::high_resolution_clock::now();

    // Add objects to vector to force move operations
    for (size_t i = 0; i < SIZE; ++i) {
        vec.emplace_back(T(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << testName << " duration: " << duration.count() << " seconds" << std::endl;
}

int main() {
    std::cout << "Performance Comparison of noexcept vs no noexcept in move constructors:\n";

    // Test class with noexcept
    

    // Test class without noexcept
    performanceTest<MyClassWithoutNoExcept>("Without noexcept");

    performanceTest<MyClassNoExcept>("With noexcept");
    return 0;
}
