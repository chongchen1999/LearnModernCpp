#include <iterator>
#include <type_traits>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <string>

// Custom namespace to avoid conflicts
namespace custom {
    // Helper concept for Equality_comparable
    template <typename A, typename B>
    constexpr bool Equality_comparable(A a, B b) {
        return std::is_same_v<A, B>;
    }

    // Define Value_type using std::iterator_traits
    template <typename Iter>
    using Value_type = typename std::iterator_traits<Iter>::value_type;

    // Define find algorithm with static assertions
    template <typename Iter, typename Val>
    Iter find(Iter b, Iter e, Val x) {
        static_assert(std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>,
                      "find() requires an input iterator");
        static_assert(std::is_same_v<typename std::iterator_traits<Iter>::value_type, Val>,
	              "find()'s iterator and value arguments must be equality comparable");
        while (b != e) {
            if (*b == x) return b;
            ++b;
        }
        return b;
    }
}

int main() {
    // Test with std::list<int>
    std::list<int> lst = {1, 2, 3, 4, 5};
    auto it = custom::find(lst.begin(), lst.end(), 3); // Use custom::find
    if (it != lst.end()) {
        std::cout << "Found: " << *it << '\n';
    } else {
        std::cout << "Not found\n";
    }

    // Test with std::vector<std::string>
    std::vector<std::string> vs = {"Hello", "World", "C++"};
    auto it2 = custom::find(vs.begin(), vs.end(), std::string("World")); // Use custom::find
    if (it2 != vs.end()) {
        std::cout << "Found: " << *it2 << '\n';
    } else {
        std::cout << "Not found\n";
    }

    return 0;
}
