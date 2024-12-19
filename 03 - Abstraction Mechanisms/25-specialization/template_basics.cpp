#include <iostream>
#include <string>
#include <vector>
#include <functional>

template<typename T>
void f(T value) {
    std::cout << "Value: " << value << "\n";
}

template<typename T>
class X {
    T member;
public:
    X(T val) : member(val) {}
    void show() { std::cout << "Member: " << member << "\n"; }
};

template<typename T, int max>
class Buffer {
    T data[max];
public:
    Buffer() { std::cout << "Buffer created with size: " << max << "\n"; }
};

// Updated Vec template to handle non-structural types
template<typename T>
class Vec {
    T data;
public:
    Vec(T default_value = T{}) : data(default_value) {}
    void show() { std::cout << "Value: " << data << "\n"; }
};

bool caseInsensitive(const std::string& a, const std::string& b) {
    return a.size() < b.size();  // Example comparison
}

template<typename Key, typename Value, typename Compare = std::less<Key>>
class Map {
    Compare cmp;
public:
    Map(Compare c = Compare{}) : cmp(c) {}
    void compare(const Key& a, const Key& b) {
        std::cout << "Comparison result: " << cmp(a, b) << "\n";
    }
};

int main() {
    // Type parameters
    f(42);
    f<std::string>("Hello");
    X<int> x1(10);
    x1.show();

    // Value parameters
    Buffer<int, 128> buf1;
    constexpr int max = 64;
    Buffer<char, max> buf2;

    // Default template arguments
    Vec<int> v1(42);
    v1.show();
    Vec<std::string> v2("Default String");
    v2.show();

    // Operations as arguments
    Map<std::string, int> map1;  // Default std::less
    map1.compare("apple", "banana");

    auto cmp = [](const std::string& a, const std::string& b) { return a > b; };
    Map<std::string, int, decltype(cmp)> map2{cmp};
    map2.compare("apple", "banana");

    return 0;
}
