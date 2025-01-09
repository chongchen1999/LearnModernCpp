#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

// Example of a simple data race
int shared_data = 0;

void increment_shared_data() {
    for (int i = 0; i < 100000; ++i) {
        shared_data++;
    }
}

// Example of avoiding a data race using a mutex
std::mutex mtx;

void increment_shared_data_mutex() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        shared_data++;
    }
}

// Example of using atomic operations to avoid data races
std::atomic<int> atomic_shared_data(0);

void increment_atomic_shared_data() {
    for (int i = 0; i < 100000; ++i) {
        atomic_shared_data++;
    }
}

int main() {
    // Data race example
    std::thread t1(increment_shared_data);
    std::thread t2(increment_shared_data);
    t1.join();
    t2.join();
    std::cout << "Shared data (without synchronization): " << shared_data << std::endl;

    // Reset shared_data
    shared_data = 0;

    // Using mutex to avoid data race
    std::thread t3(increment_shared_data_mutex);
    std::thread t4(increment_shared_data_mutex);
    t3.join();
    t4.join();
    std::cout << "Shared data (with mutex): " << shared_data << std::endl;

    // Using atomic to avoid data race
    std::thread t5(increment_atomic_shared_data);
    std::thread t6(increment_atomic_shared_data);
    t5.join();
    t6.join();
    std::cout << "Atomic shared data: " << atomic_shared_data << std::endl;

    return 0;
}