#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>

// Atomic Counter Example
std::atomic<int> counter(0);

void increment_counter() {
    for (int i = 0; i < 1000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

// Double-Checked Locking Idiom Example
class Singleton {
public:
    static Singleton* getInstance() {
        Singleton* instance = instance_flag.load(std::memory_order_acquire);
        if (!instance) {
            std::lock_guard<std::mutex> lock(mutex);
            instance = instance_flag.load(std::memory_order_relaxed);
            if (!instance) {
                instance = new Singleton();
                instance_flag.store(instance, std::memory_order_release);
            }
        }
        return instance;
    }

private:
    Singleton() {}
    static std::atomic<Singleton*> instance_flag;
    static std::mutex mutex;
};

std::atomic<Singleton*> Singleton::instance_flag(nullptr);
std::mutex Singleton::mutex;

// volatile Keyword Example
volatile int hardware_register = 0;

int main() {
    // Atomic Counter Example
    std::thread t1(increment_counter);
    std::thread t2(increment_counter);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter.load() << std::endl;

    // Double-Checked Locking Idiom Example
    Singleton* instance = Singleton::getInstance();
    std::cout << "Singleton instance created." << std::endl;

    // volatile Keyword Example
    int t1_ = hardware_register;
    int t2_ = hardware_register;

    std::cout << "t1: " << t1_ << ", t2: " << t2_ << std::endl;

    return 0;
}