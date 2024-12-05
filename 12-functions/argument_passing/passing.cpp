#include <iostream>
#include <vector>

// 1. Local Variables and `static` Keyword
void exampleStaticVariables(int a) {
    while (a--) {
        static int n = 0; // Initialized only once
        int x = 0;        // Initialized every time `exampleStaticVariables` is called
        std::cout << "n == " << n++ << ", x == " << x++ << '\n';
    }
}

// 2. Reference Arguments
void modify(int val, int& ref) {
    ++val;  // Increments local copy
    ++ref;  // Increments the original variable
}

// 3. Argument Passing with Large Objects
class Large {
public:
    int data[1000];
};
void printLarge(const Large& large) { 
    std::cout << "Large object accessed efficiently\n";
}

// 4. Array Arguments, the arr will decay to a pointer
void printArray(const int (&arr)[10], int size) {
    std::cout << sizeof(arr) << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

// 5. Using Templates with Arrays
template<typename T, int N>
void printTemplateArray(T (&arr)[N]) {
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

template <int N>
void printArray(int (&arr)[N]) {
    for (int &x : arr) {
        std::cout << x << " ";
    }
    std::cout << '\n';
}

// 6. Passing Rvalue References
void process(std::vector<int>&& data) {
    std::cout << "Processing move-only data\n";
    std::cout << "Size: " << data.size() << '\n';
    std::cout << &data << std::endl;
}

// Main Function
int main() {
    // Example 1: Local Variables and `static`
    std::cout << "Static Variable Example:\n";
    exampleStaticVariables(3);
    exampleStaticVariables(2);

    // Example 2: Reference Arguments
    std::cout << "\nReference Arguments Example:\n";
    int x = 1, y = 1;
    modify(x, y);
    std::cout << "x = " << x << ", y = " << y << '\n';

    // Example 3: Argument Passing with Large Objects
    std::cout << "\nArgument Passing with Large Objects:\n";
    Large obj;
    printLarge(obj);

    // Example 4: Array Arguments
    std::cout << "\nArray Arguments Example:\n";
    int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << sizeof(nums) << std::endl;
    printArray(nums, 4);

    // Example 5: Using Templates with Arrays
    std::cout << "\nTemplate with Arrays Example:\n";
    printTemplateArray(nums);
    std::cout << "Print Array:\n";
    printArray(nums);

    // Example 6: Rvalue References
    std::cout << "\nRvalue References Example:\n";
    process(std::vector<int>{1, 2, 3});

    return 0;
}
