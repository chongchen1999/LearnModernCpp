#include <iostream>
#include <string>
#include <type_traits>
#include <array>

// Maximum size allowed for stack allocation
constexpr int on_stack_max = sizeof(std::string);

// Scoped: Allocates the object directly on the stack
template<typename T>
struct Scoped {
    T& operator*() { return x; }
    T* operator->() { return &x; }

    Scoped() = default;  // Add default constructor
    Scoped(const Scoped&) = delete; // Prevent copying
    Scoped& operator=(const Scoped&) = delete;

private:
    T x; // Object stored on the stack
};

// On_heap: Allocates the object dynamically on the heap
template<typename T>
struct On_heap {
    On_heap() : p(new T) { }      // Allocate
    ~On_heap() { delete p; }     // Deallocate

    T& operator*() { return *p; }
    T* operator->() { return p; }

    On_heap(const On_heap&) = delete; // Prevent copying
    On_heap& operator=(const On_heap&) = delete;

private:
    T* p; // Pointer to the heap-allocated object
};

// Obj_holder: Selects allocation strategy based on object size
template<typename T>
struct Obj_holder {
    using type = typename std::conditional<
        (sizeof(T) <= on_stack_max),
        Scoped<T>,  // Use stack if size is small
        On_heap<T>  // Use heap if size is large
    >::type;
};

int main() {
    // Create objects using the type alias for cleaner syntax
    using SmallObj = typename Obj_holder<double>::type;
    using LargeObj = typename Obj_holder<std::array<double, 200>>::type;

    SmallObj small_obj;  // Allocates on the stack
    *small_obj = 7.7;
    std::cout << "Small object: " << *small_obj << std::endl;

    LargeObj large_obj;  // Allocates on the heap
    (*large_obj)[0] = 9.9;  // Fixed array access syntax
    std::cout << "Large object: " << (*large_obj)[0] << std::endl;

    return 0;
}