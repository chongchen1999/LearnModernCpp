#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // Simple lambda for printing each number
    std::for_each(nums.begin(), nums.end(),
                  [](const int &n) { std::cout << n << " "; });
    std::cout << "\n";
    return 0;
}
