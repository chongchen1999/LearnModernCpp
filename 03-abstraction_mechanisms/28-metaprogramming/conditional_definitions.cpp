#include <type_traits>
#include <iostream>
#include <vector>
#include <complex>
#include <iterator>
#include <utility>

// Simplify type checks
template <typename T>
constexpr bool Is_class() {
    return std::is_class<T>::value;
}

// Smart pointer class
template <typename T>
class Smart_pointer {
public:
    // Add const correctness
    T& operator*() const {
        return *ptr;
    }

    // Fix operator-> to be const-correct and return raw pointer
    template <typename U = T>
    typename std::enable_if<Is_class<U>(), U*>::type operator->() const {
        return ptr;
    }

    // Delete copy constructor and assignment operator to prevent double deletion
    Smart_pointer(const Smart_pointer&) = delete;
    Smart_pointer& operator=(const Smart_pointer&) = delete;

    // Add move operations
    Smart_pointer(Smart_pointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    Smart_pointer& operator=(Smart_pointer&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    explicit Smart_pointer(T* p) : ptr(p) {}
    ~Smart_pointer() { delete ptr; }

private:
    T* ptr;
};

// Example use of Smart_pointer
void example_smart_pointer() {
    Smart_pointer<int> p1(new int(42));
    Smart_pointer<std::complex<double>> p2(new std::complex<double>(3, 4));

    std::cout << *p1 << '\n';
    std::cout << p2->real() << '\n';
}

// Improved Input Iterator detection
template <typename Iter, typename = void>
struct is_input_iterator : std::false_type {};

template <typename Iter>
struct is_input_iterator<
    Iter,
    typename std::enable_if<
        std::is_base_of<
            std::input_iterator_tag,
            typename std::iterator_traits<Iter>::iterator_category
        >::value ||
        std::is_pointer<Iter>::value
    >::type
> : std::true_type {};

template <typename Iter>
constexpr bool Input_iterator() {
    return is_input_iterator<Iter>::value;
}

// Custom vector with conditional constructors
template <typename T>
class MyVector {
public:
    // Add noexcept specification
    MyVector(size_t n, const T& val) noexcept(
        std::is_nothrow_copy_constructible<T>::value
    ) {
        data.resize(n, val);
    }

    template <typename Iter>
    MyVector(Iter first, Iter last,
        typename std::enable_if<Input_iterator<Iter>()>::type* = nullptr
    ) {
        data.reserve(std::distance(first, last)); // Optimization
        while (first != last) {
            data.push_back(*first);
            ++first;
        }
    }

    void print() const {
        for (const auto& elem : data) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }

private:
    std::vector<T> data;
};

// Example use of MyVector
void example_my_vector() {
    MyVector<int> v1(5, 10);
    v1.print();

    int arr[] = {1, 2, 3, 4};
    MyVector<int> v2(std::begin(arr), std::end(arr));
    v2.print();
}

// Forward declare f before the has_f trait
void f(int x);

// Improved SFINAE detection
namespace detail {
    template <typename T>
    auto has_f_impl(int) -> decltype(f(std::declval<T>()), std::true_type{});

    template <typename T>
    std::false_type has_f_impl(...);
}

template <typename T>
struct has_f : decltype(detail::has_f_impl<T>(0)) {};

// Custom function that uses has_f
template <typename T>
typename std::enable_if<has_f<T>::value>::type use_f(const T& t) {
    f(t);
}

// Implementation of f
void f(int x) {
    std::cout << "f(" << x << ")\n";
}

// Example usage
void example_has_f() {
    static_assert(has_f<int>::value, "int should have f()");
    use_f(10);
}

int main() {
    try {
        example_smart_pointer();
        example_my_vector();
        example_has_f();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}