#include <iostream>
#include <utility>

// Base case: empty tuple
template <typename... Types>
class MyTuple {};

// Recursive case: a tuple with at least one type
template <typename First, typename... Rest>
class MyTuple<First, Rest...> : private MyTuple<Rest...> {
    using Base = MyTuple<Rest...>;

public:
    First value;

    // Constructor
    MyTuple(First v, Rest... rest) : Base(rest...), value(v) {}

    // Access element at index 0
    First& getValue() { return value; }
    const First& getValue() const { return value; }

    // Recursively access elements in the rest of the tuple
    template <std::size_t Index>
    auto& get() {
        if constexpr (Index == 0) {
            return value;
        } else {
            return Base::template get<Index - 1>();
        }
    }

    template <std::size_t Index>
    const auto& get() const {
        if constexpr (Index == 0) {
            return value;
        } else {
            return Base::template get<Index - 1>();
        }
    }
};

// Helper function to create a tuple
template <typename... Types>
MyTuple<Types...> makeMyTuple(Types... args) {
    return MyTuple<Types...>(args...);
}

int main() {
    auto myTuple = makeMyTuple(42, 3.14, "Hello");

    std::cout << "First element: " << myTuple.get<0>() << '\n';
    std::cout << "Second element: " << myTuple.get<1>() << '\n';
    std::cout << "Third element: " << myTuple.get<2>() << '\n';

    return 0;
}
