#include <atomic>
#include <iostream>
#include <thread>
#include <memory>

// Forward declaration for the ABA problem example
struct Link {
    int data;
    Link* next;
    Link(int d, Link* n) : data(d), next(n) {}
};
std::atomic<Link*> head{nullptr};

// Example of relaxed memory order
void relaxed_memory_order_example() {
    std::atomic<int> x, y;
    // Simulating two threads
    auto thread1 = [&]() {
        int r1 = y.load(std::memory_order_relaxed);
        x.store(r1, std::memory_order_relaxed);
    };
    auto thread2 = [&]() {
        int r2 = x.load(std::memory_order_relaxed);
        y.store(42, std::memory_order_relaxed);
    };
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join();
    t2.join();
    std::cout << "Relaxed memory order example, possible non - intuitive results" << std::endl;
}

// Example of using atomic for a shared counter
template<typename T>
class shared_ptr {
public:
    ~shared_ptr()
    {
        if (--*puc) delete p;
    }
private:
    T* p;
    std::atomic<int>* puc;
};

// The classic compare - and - swap loop
void compare_and_swap_loop() {
    std::atomic<int> val = 0;
    int expected = val.load();
    auto fct = [](int e) { return e + 1; };
    int next; // Declare 'next' outside the block
    do {
        next = fct(expected); // Update 'next' inside the loop
    } while (!val.compare_exchange_weak(expected, next));
    std::cout << "Compare - and - swap loop completed, final val: " << val.load() << std::endl;
}


// ABA problem example
void aba_problem_example() {
    // Assume head is initialized somewhere
    int data = 10;
    Link* nh = new Link(data, nullptr);
    Link* h = head.load();
    do {
        if (h->data < data) break;
        nh->next = h;
    } while (!head.compare_exchange_weak(h, nh));
    std::cout << "ABA problem example, be aware of potential data integrity issues" << std::endl;
}

// Using atomic_flag as a spin lock
class spin_mutex {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() { while(flag.test_and_set()); }
    void unlock() { flag.clear(); }
};

// volatile example
void volatile_example() {
    volatile const long clock_register = 0;
    auto t1 = clock_register;
    //... no use of clock_register here...
    auto t2 = clock_register;
    std::cout << "Volatile example, compiler won't optimize away redundant reads" << std::endl;
}


int main() {
    relaxed_memory_order_example();
    compare_and_swap_loop();
    // aba_problem_example(); // Needs proper head initialization
    volatile_example();
    return 0;
}