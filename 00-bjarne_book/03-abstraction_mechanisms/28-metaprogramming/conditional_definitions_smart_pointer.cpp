#include <iostream>
#include <complex>

// Smart pointer class
template <typename T>
class Smart_pointer {
private:
    T* ptr;

public:
    Smart_pointer(const Smart_pointer&) = delete;
    Smart_pointer& operator=(const Smart_pointer&) = delete;

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

    T& operator*() const {
        return *ptr;
    }

    T* get() const {
        return ptr;
    }

    T* operator->() const 
    requires std::is_class_v<T> {
        return ptr;
    }
};

// Example use of Smart_pointer
void example_smart_pointer() {
    Smart_pointer<int> p1(new int(42));
    Smart_pointer<std::complex<double>> p2(new std::complex<double>(3, 4));

    std::cout << *p1 << '\n';
    std::cout << p2->real() << '\n';
}

int main() {
    example_smart_pointer();
    return 0;
}