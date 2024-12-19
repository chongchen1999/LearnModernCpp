#include <iostream>
#include <cstdlib>
#include <new> // For std::bad_alloc

class Employee {
public:
    // Overloaded operator new
    void* operator new(size_t size) {
        std::cout << "Allocating " << size << " bytes for Employee\n";
        void* ptr = std::malloc(size); // Allocate memory
        if (!ptr) throw std::bad_alloc(); // Throw exception if allocation fails
        return ptr;
    }

    // Overloaded operator delete
    void operator delete(void* ptr, size_t size) {
        if (ptr) {
            std::cout << "Deallocating " << size << " bytes for Employee\n";
            std::free(ptr); // Free the allocated memory
        }
    }

    // Overloaded operator new[] (for arrays)
    void* operator new[](size_t size) {
        std::cout << "Allocating array of size " << size << " bytes for Employee\n";
        void* ptr = std::malloc(size);
        if (!ptr) throw std::bad_alloc();
        return ptr;
    }

    // Overloaded operator delete[] (for arrays)
    void operator delete[](void* ptr, size_t size) {
        if (ptr) {
            std::cout << "Deallocating array of size " << size << " bytes for Employee\n";
            std::free(ptr);
        }
    }
};

// Example usage
int main() {
    // Single object allocation and deallocation
    Employee* e = new Employee;
    delete e;

    // Array allocation and deallocation
    Employee* eArray = new Employee[3];
    delete[] eArray;

    return 0;
}
