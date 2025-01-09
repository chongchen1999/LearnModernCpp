#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <regex>

bool customComparator(int a, int b) {
    return a > b; // Descending order
}

int main() {
    // Example 1: Sorting a vector
    std::vector<int> nums = {4, 2, 3, 1};
    std::sort(nums.begin(), nums.end()); // Sort in ascending order
    std::cout << "Sorted in ascending order: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Example 2: Sorting with a custom comparator
    std::sort(nums.begin(), nums.end(), customComparator); // Sort in descending order
    std::cout << "Sorted in descending order: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Example 3: Using math functions
    double x = 16.0;
    std::cout << "Square root of " << x << " is " << std::sqrt(x) << std::endl;

    // Example 4: Using regex
    std::string s = "abc123";
    std::regex pattern("[a-z]+\\d+");
    if (std::regex_match(s, pattern)) {
        std::cout << "Match found!" << std::endl;
    } else {
        std::cout << "No match!" << std::endl;
    }

    return 0;
}
