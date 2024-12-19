#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

// Concept: Regular (default constructible, copyable, comparable)
template<typename T>
concept Regular = 
    std::default_initializable<T> && 
    std::copyable<T> &&
    requires(T a, T b) {
        { a == b } -> std::convertible_to<bool>;
        { a != b } -> std::convertible_to<bool>;
    };

// Concept: Ordered (Regular + <)
template<typename T>
concept Ordered = Regular<T> &&
    requires(T a, T b) {
        { a < b } -> std::convertible_to<bool>;
    };

// Example: String template
template<Ordered C>
class String {
private:
    std::vector<C> data;
public:
    String() = default;
    String(const String& other) = default;
    String& operator=(const String& other) = default;

    // Add elements to the string
    void add(const C& c) { data.push_back(c); }

    // Compare Strings
    bool operator==(const String& other) const { return data == other.data; }
    bool operator!=(const String& other) const { return data != other.data; }

    // Ordering
    bool operator<(const String& other) const { return data < other.data; }

    // Output
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        for (const auto& c : s.data) os << c;
        return os;
    }
};

// Example: Balancer for binary trees
struct RedBlackBalancer {
    template<typename Node>
    static void add_fixup(Node* x) { /* implementation */ }

    template<typename Node>
    static void touch(Node* x) { /* implementation */ }

    template<typename Node>
    static void detach(Node* x) { /* implementation */ }
};

int main() {
    // String example
    String<char> s1, s2;
    s1.add('a');
    s1.add('b');
    s2.add('a');
    s2.add('b');

    if (s1 == s2) std::cout << "Strings are equal\n";
    std::cout << "String: " << s1 << '\n';

    return 0;
}
