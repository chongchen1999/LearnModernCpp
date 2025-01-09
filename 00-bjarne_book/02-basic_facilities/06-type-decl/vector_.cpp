#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {1, 2};
    for (int i = 1; i < 4096; ++i) {
        v1.emplace_back(i);
    }

    std::cout << sizeof(v1) << ' ' << sizeof(v2) << std::endl;
    return 0;
}