#include <iostream>

class Arena {
public:
    virtual void* alloc(size_t size) = 0; // Allocate memory
    virtual void free(void* ptr) = 0;     // Free memory
};

class PersistentArena : public Arena {
public:
    void* alloc(size_t size) override {
        std::cout << "Allocating " << size << " bytes in PersistentArena\n";
        return ::operator new(size); // Use global new for simplicity
    }

    void free(void* ptr) override {
        std::cout << "Freeing memory in PersistentArena\n";
        ::operator delete(ptr);
    }
};

// Custom placement new using Arena
void* operator new(size_t size, Arena* arena) noexcept {
    return arena->alloc(size);
}

class X {
public:
    X(int value) : val(value) {
        std::cout << "X constructed with value: " << val << '\n';
    }
    ~X() {
        std::cout << "X destructed with value: " << val << '\n';
    }
private:
    int val;
};

int main() {
    PersistentArena arena;

    // Allocate an X object in PersistentArena
    X* obj = new (&arena) X(100);

    // Explicit cleanup
    obj->~X();           // Destroy the object
    arena.free(obj);      // Free the memory manually

    return 0;
}
