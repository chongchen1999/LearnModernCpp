#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cctype>

// Sort template with custom comparator
template<typename T, typename Compare = std::less<T>>
void sort(std::vector<T>& v) {
    Compare cmp;
    const size_t n = v.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            for (int j = i - gap; j >= 0; j -= gap) {
                if (cmp(v[j + gap], v[j])) {
                    std::swap(v[j], v[j + gap]);
                }
            }
        }
    }
}

// Custom case-insensitive comparison
struct NoCase {
    bool operator()(const std::string& a, const std::string& b) const {
        return std::lexicographical_compare(
            a.begin(), a.end(), b.begin(), b.end(),
            [](unsigned char ac, unsigned char bc) { return tolower(ac) < tolower(bc); });
    }
};

// Xref class to demonstrate ownership
template<typename T>
class Xref {
    int index;
    T* elem;
    bool owned;

public:
    Xref(int i, T&& r) : index{i}, elem{new T{std::move(r)}}, owned{true} {
        std::cout << "move constructor\n";
    }
    Xref(int i, T& r) : index{i}, elem{&r}, owned{false} {
        std::cout << "copy constructor\n";
    }
    ~Xref() {
        if (owned) delete elem;
    }
};

// Factory function using forwarding
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    std::vector<int> vi = {4, 1, 3};
    std::vector<std::string> vs = {"Banana", "apple", "cherry"};

    sort<int>(vi);
    sort<std::string, NoCase>(vs);

    for (int i : vi) std::cout << i << " ";
    std::cout << "\n";

    for (const auto& s : vs) std::cout << s << " ";
    std::cout << "\n";

    std::string x = "example";
    auto ptr = std::make_unique<Xref<std::string>>(1, std::move(x));

    return 0;
}
