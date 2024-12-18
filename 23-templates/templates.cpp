#include <iostream>
#include <vector>

// Example 1: Class Template
template<typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T getValue() { return value; }
};

// Example 2: Class Template with Array Management
template<typename T>
class MyVector {
    T* data;
    size_t size;
public:
    MyVector(size_t n) : size(n), data(new T[n]) {}
    ~MyVector() { delete[] data; }
    T& operator[](size_t i) { return data[i]; }
};

// Example 3: Function Template
template<typename T>
T add(T a, T b) {
    return a + b;
}

// Example 4: Template Alias
template<typename T>
using Vec = std::vector<T>;

// Example 5: Template Specialization
template<typename T>
class Printer {
public:
    void print(T value) {
        std::cout << value << '\n';
    }
};

template<>
class Printer<bool> {
public:
    void print(bool value) {
        std::cout << (value ? "true" : "false") << '\n';
    }
};

// Example 6: Variadic Template
template<typename... Args>
void printAll(Args... args) {
    (std::cout << ... << args) << '\n';
}

int main() {
    // Class Template Example
    Box<int> intBox(10);
    Box<double> doubleBox(3.14);
    std::cout << "Box<int>: " << intBox.getValue() << '\n';
    std::cout << "Box<double>: " << doubleBox.getValue() << '\n';

    // Vector Template Example
    MyVector<int> vec(10);
    vec[0] = 42;
    std::cout << "MyVector<int>[0]: " << vec[0] << '\n';

    // Function Template Example
    std::cout << "Add ints: " << add(3, 4) << '\n';
    std::cout << "Add doubles: " << add(3.5, 4.2) << '\n';

    // Template Alias Example
    Vec<int> numbers = {1, 2, 3, 4};
    std::cout << "Vec<int>: ";
    for (int n : numbers) std::cout << n << ' ';
    std::cout << '\n';

    // Template Specialization Example
    Printer<int> intPrinter;
    intPrinter.print(42);

    Printer<bool> boolPrinter;
    boolPrinter.print(true);

    // Variadic Template Example
    printAll(1, " + ", 2, " = ", 3);
}
