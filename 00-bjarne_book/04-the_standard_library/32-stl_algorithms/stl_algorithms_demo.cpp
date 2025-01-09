// stl_algorithms_demo.cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdexcept>

// Example 1: Copy
void example_copy() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2(3);

    std::copy(v1.begin(), v1.end(), v2.begin());

    for (int x : v2) {
        std::cout << x << " "; // Output: 1 2 3
    }
}

// Example 2: Safe Copy
template <typename Cont1, typename Cont2>
void safe_copy(const Cont1& source, Cont2& target) {
    if (target.size() < source.size()) {
        throw std::out_of_range("Target container is too small");
    }
    std::copy(source.begin(), source.end(), target.begin());
}

// Example 3: Sort
void example_sort() {
    std::vector<int> v = {3, 1, 4, 1, 5};
    std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });

    for (int x : v) {
        std::cout << x << " "; // Output: 5 4 3 1 1
    }
}

// Example 4: Safe Sort
template <typename Cont>
void safe_sort(Cont& c) {
    std::sort(c.begin(), c.end());
}

// Example 5: Find All
template <typename Cont, typename Pred>
std::vector<typename Cont::value_type*> find_all(Cont& c, Pred p) {
    std::vector<typename Cont::value_type*> result;
    for (auto& x : c) {
        if (p(x)) {
            result.push_back(&x);
        }
    }
    return result;
}

// Example 6: Predicate Find
void example_find_if() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x > 3; });
    if (it != v.end()) {
        std::cout << *it; // Output: 4
    }
}

int main() {
    example_copy();
    example_sort();
    example_find_if();
    return 0;
}
