#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <type_traits>
#include <limits>
#include <stdexcept>

namespace memory_management {

// Arena class for custom memory management
class Arena {
private:
    std::unique_ptr<char[]> memory;
    size_t size;
    size_t used{0};

public:
    Arena(size_t s) : memory(std::make_unique<char[]>(s)), size(s) {}
    
    void* allocate(size_t bytes) {
        if (used + bytes > size) {
            throw std::bad_alloc();
        }
        void* result = memory.get() + used;
        used += bytes;
        return result;
    }

    void reset() {
        used = 0;
    }

    size_t available() const {
        return size - used;
    }

    ~Arena() = default;

    // Prevent copying
    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;
    
    // Allow moving
    Arena(Arena&&) = default;
    Arena& operator=(Arena&&) = default;
};

// Simple allocator implementation
template<typename T>
class SimpleAllocator {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;

    SimpleAllocator() noexcept = default;
    template<typename U>
    SimpleAllocator(const SimpleAllocator<U>&) noexcept {}

    T* allocate(size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }
        if (auto p = static_cast<T*>(::operator new(n * sizeof(T), std::nothrow))) {
            return p;
        }
        throw std::bad_alloc();
    }

    void deallocate(T* p, size_t) noexcept {
        ::operator delete(p);
    }
};

template<typename T, typename U>
bool operator==(const SimpleAllocator<T>&, const SimpleAllocator<U>&) noexcept {
    return true;
}

template<typename T, typename U>
bool operator!=(const SimpleAllocator<T>&, const SimpleAllocator<U>&) noexcept {
    return false;
}

// Arena-based allocator
template<typename T>
class ArenaAllocator {
private:
    Arena* arena;

public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;

    explicit ArenaAllocator(Arena& a) noexcept : arena(&a) {}
    
    template<typename U>
    ArenaAllocator(const ArenaAllocator<U>& other) noexcept : arena(other.arena) {}

    T* allocate(size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(arena->allocate(n * sizeof(T)));
    }

    void deallocate(T*, size_t) noexcept {
        // Arena handles deallocation
    }

    Arena* get_arena() const noexcept { return arena; }
};

template<typename T, typename U>
bool operator==(const ArenaAllocator<T>& a, const ArenaAllocator<U>& b) noexcept {
    return a.get_arena() == b.get_arena();
}

template<typename T, typename U>
bool operator!=(const ArenaAllocator<T>& a, const ArenaAllocator<U>& b) noexcept {
    return !(a == b);
}

} // namespace memory_management

int main() {
    using namespace memory_management;
    
    try {
        // Create arenas with different sizes
        constexpr size_t SMALL_ARENA_SIZE = 100'000;
        constexpr size_t LARGE_ARENA_SIZE = 1'000'000;
        
        Arena small_arena(SMALL_ARENA_SIZE);
        Arena large_arena(LARGE_ARENA_SIZE);

        // Standard vector with default allocator
        std::vector<int> v1;
        v1.push_back(42);

        // Vector with simple allocator
        std::vector<int, SimpleAllocator<int>> v2;
        v2.push_back(42);

        // Vector with arena allocator
        std::vector<int, ArenaAllocator<int>> v3{ArenaAllocator<int>(small_arena)};
        v3.push_back(42);

        // String with arena allocator
        using ArenaString = std::basic_string<char, std::char_traits<char>, ArenaAllocator<char>>;
        ArenaString str{ArenaAllocator<char>(large_arena)};
        str = "Hello, Arena!";

        // Vector of arena-allocated strings
        std::vector<ArenaString, ArenaAllocator<ArenaString>> v4{ArenaAllocator<ArenaString>(large_arena)};
        v4.push_back(str);

        std::cout << "Successfully created and used various allocators\n";
        std::cout << "Small arena available memory: " << small_arena.available() << " bytes\n";
        std::cout << "Large arena available memory: " << large_arena.available() << " bytes\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}