#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // A vector of integers
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Lambda using FTADLE: The type of 'T' will be deduced automatically
    auto print = [](const auto& element) {
        std::cout << element << " ";
    };

    // Use FTADLE to create a transformation lambda
    auto multiply = []<typename T>(T x, T multiplier) {
        return x * multiplier;
    };

    // Print the elements using the print lambda
    std::for_each(vec.begin(), vec.end(), print);
    std::cout << std::endl;

    // Use multiply lambda with FTADLE to transform elements
    std::vector<int> transformed;
    std::transform(vec.begin(), vec.end(), std::back_inserter(transformed), 
                   [&](int x) { return multiply(x, 2); });

    // Print transformed elements
    std::for_each(transformed.begin(), transformed.end(), print);
    std::cout << std::endl;

    return 0;
}
