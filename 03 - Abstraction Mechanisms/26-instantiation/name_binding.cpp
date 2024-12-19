#include <iostream>
#include <vector>
#include <algorithm>

// Example struct
struct Quad {
    int x;
    bool operator<(const Quad& other) const {
        return x < other.x;
    }
};

// Overload operator<< as a free function
std::ostream& operator<<(std::ostream& os, const Quad& q) {
    os << "Quad(" << q.x << ")";
    return os;
}

// Function avoiding nonlocal names by parameterization
template<typename T, typename Sort, typename Ostream>
void print_sorted_custom(std::vector<T>& v, Sort sort_func, Ostream& os) {
    sort_func(v.begin(), v.end());
    for (const auto& x : v) {
        os << x << '\n';
    }
}

// Main function to demonstrate usage
int main() {
    Quad q1{1}, q2{2};
    std::vector<Quad> vec = {q2, q1}; // Unsorted vector

    // Using print_sorted_custom
    print_sorted_custom(vec, std::sort<std::vector<Quad>::iterator>, std::cout);

    return 0;
}
