#include <ratio>
#include <type_traits>
#include <iostream>

// Static assertions to test ratio arithmetic
static_assert(std::ratio_add<std::ratio<1, 3>, std::ratio<1, 6>>::num == 1, "problem: 1/3+1/6!= 1/2");
static_assert(std::ratio_add<std::ratio<1, 3>, std::ratio<1, 6>>::den == 2, "problem: 1/3+1/6!= 1/2");
static_assert(std::ratio_multiply<std::ratio<1, 3>, std::ratio<3, 2>>::num == 1, "problem: 1/3∗3/2!= 1/2");
static_assert(std::ratio_multiply<std::ratio<1, 3>, std::ratio<3, 2>>::den == 2, "problem: 1/3∗3/2!= 1/2");

// Type traits examples
template<typename T>
void f_(T& a) {
    static_assert(std::is_floating_point<T>::value, "FP type expected");
    std::cout << "The type is a floating - point type." << std::endl;
}

class MyClass {
public:
    MyClass() = default;
    MyClass(const MyClass&) = default;
};

class NoCopyClass {
public:
    NoCopyClass() = default;
    NoCopyClass(const NoCopyClass&) = delete;
};

// Type generators examples
template<typename T>
void f(T v) {
    typename std::remove_reference<T>::type x = v;
    T y = v;
    std::cout << "Type of x: " << typeid(x).name() << std::endl;
    std::cout << "Type of y: " << typeid(y).name() << std::endl;
}


int main() {
    // Ratio operations
    // No need to print results here as static assertions are used for verification

    // Type traits
    double d = 1.0;
    f_(d);
    // int i = 1; f(i); // This would cause a static assertion failure
    std::cout << "MyClass is copy - constructible: " << std::is_copy_constructible<MyClass>::value << std::endl;
    std::cout << "NoCopyClass is copy - constructible: " << std::is_copy_constructible<NoCopyClass>::value << std::endl;

    // Type generators
    const int ci = 1;
    using NonConstInt = typename std::remove_const<decltype(ci)>::type;
    NonConstInt ni = 2;
    std::cout << "Type after removing const: " << typeid(ni).name() << std::endl;

    int i = 1;
    f(i);
    int& ri = i;
    f(ri);

    int a[10][20];
    using Array10 = typename std::remove_extent<decltype(a)>::type;
    using BaseType = typename std::remove_all_extents<decltype(a)>::type;
    std::cout << "Type after removing one extent: " << typeid(Array10).name() << std::endl;
    std::cout << "Type after removing all extents: " << typeid(BaseType).name() << std::endl;

    return 0;
}