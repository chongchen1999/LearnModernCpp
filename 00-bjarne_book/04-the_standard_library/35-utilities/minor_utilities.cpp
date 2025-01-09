#include <iostream>
#include <utility>
#include <vector>
#include <typeindex>
#include <unordered_map>

// move() example
void consume(std::vector<int>&& v) {
    std::cout << "Consuming vector with size: " << v.size() << std::endl;
}

// forward() example
template<typename T>
void printer(T&& t) {
    std::cout << "Printing: " << t << std::endl;
}

template<typename T>
void forwarder(T&& t) {
    printer(std::forward<T>(t));
}

// swap() example
// swap() code is already part of the standard library, this is just for demonstration
// template<typename T>
// void swap(T& a, T& b) noexcept(Is_nothrow_move_constructible<T>()
//     && Is_nothrow_move_assignable<T>()) {
//     T tmp{move(a)};
//     a = move(b);
//     b = move(tmp);
// }

// Relational operators example
struct Val {
    double d;
    bool operator==(Val v) const { return v.d == d; }
    bool operator<(Val v) const { return d < v.d; }
    bool operator>(Val v) const { return d > v.d; }
};

void my_algo(std::vector<Val>& vv) {
    using namespace std::rel_ops;
    for (size_t i = 0; i < vv.size(); ++i) {
        if (Val{} > vv[i]) {
            // Assuming an abs function for Val is defined properly
        }
    }
}

// Comparing and Hashing type_info example
int main() {
    // move() example
    std::vector<int> v = {1, 2, 3};
    consume(std::move(v));

    // forward() example
    int i = 42;
    forwarder(i);
    forwarder(42);

    // swap() example
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    std::swap(v1, v2);

    // Relational operators example
    std::vector<Val> vv;
    my_algo(vv);

    // Comparing and Hashing type_info example
    std::unordered_map<std::type_index, const std::type_info*> types;
    int num = 0;
    types[std::type_index(typeid(num))] = &typeid(num);

    return 0;
}