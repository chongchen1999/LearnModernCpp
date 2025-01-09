#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

// Global registry for active threads
std::vector<std::thread::id> active_threads;
std::mutex thread_mutex;

// Function executed by threads
void worker(int id) {
    {
        std::lock_guard<std::mutex> lock(thread_mutex);
        active_threads.push_back(std::this_thread::get_id());
    }
    std::cout << "Thread " << id << " started with ID: " 
              << std::this_thread::get_id() << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
}

void print_all_threads() {
    std::lock_guard<std::mutex> lock(thread_mutex);
    std::cout << "Currently running threads:\n";
    for (const auto& id : active_threads) {
        std::cout << "Thread ID: " << id << '\n';
    }
    std::cout << "-----------------------\n";
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(worker, i); // Create a new thread
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Short delay
        print_all_threads(); // Print all running threads
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All threads have completed.\n";
    return 0;
}
