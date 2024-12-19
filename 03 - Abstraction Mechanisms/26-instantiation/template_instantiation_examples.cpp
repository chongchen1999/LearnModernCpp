#include <iostream>
#include <vector>
#include <string>

// Example 1: Template Class
template <typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() { return value; }
};

// Example 2: Template Function
template <typename T>
void printValue(T value) {
    std::cout << "Value: " << value << std::endl;
}

// Example 3: Partial Instantiation
template <typename T>
class List {
public:
    void sort() {
        std::cout << "Sorting List!" << std::endl;
    }
};

// Example 4: Extern Templates
// Declare a template class
template <typename T>
class MyVector {
public:
    void push_back(T value) {
        std::cout << "Added value: " << value << std::endl;
    }
};

// Explicit instantiation
template class MyVector<int>;

// Main function
int main() {
    // Example 1: Box instantiation
    Box<int> intBox(10);
    std::cout << "Box<int>: " << intBox.get() << std::endl;

    Box<std::string> strBox("Hello");
    std::cout << "Box<std::string>: " << strBox.get() << std::endl;

    // Example 2: Function instantiation
    printValue(42);
    printValue("Template Function");

    // Example 3: Conditional instantiation
    List<int> intList;
    intList.sort(); // Only instantiates List<int>::sort()

    // Example 4: Using explicitly instantiated templates
    MyVector<int> vec;
    vec.push_back(5);

    return 0;
}
