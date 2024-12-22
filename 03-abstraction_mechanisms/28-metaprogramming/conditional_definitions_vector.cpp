#include <vector>
#include <iterator>
#include <type_traits>
#include <iostream>

// Concept for Input Iterator detection
template <typename Iter>
concept InputIterator = requires(Iter it) {
    typename std::iterator_traits<Iter>::iterator_category;
    { *it } -> std::same_as<typename std::iterator_traits<Iter>::reference>;
    { ++it } -> std::same_as<Iter&>;
};

// Custom vector with conditional constructors using concepts
template <typename T>
class MyVector {
private:
    std::vector<T> data;

public:
    // Constructor with a size and value
    MyVector(size_t n, const T& val) noexcept(
        std::is_nothrow_copy_constructible<T>::value
    ) {
        data.resize(n, val);
    }

    // Constructor that takes a range (InputIterator)
    template <typename Iter>
    requires InputIterator<Iter>
    MyVector(Iter first, Iter last) {
        data.reserve(std::distance(first, last)); // Optimization
        while (first != last) {
            data.push_back(*first);
            ++first;
        }
    }

    // Print the contents of the vector
    void print() const {
        for (const auto& elem : data) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
};

// Example use of MyVector
void example_my_vector() {
    MyVector<int> v1(5, 10);
    v1.print();

    int arr[] = {1, 2, 3, 4};
    MyVector<int> v2(std::begin(arr), std::end(arr));
    v2.print();
}

int main() {
    example_my_vector();
}
