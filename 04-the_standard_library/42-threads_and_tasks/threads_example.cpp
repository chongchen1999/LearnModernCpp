// threads_example.cpp
#include <thread>
#include <vector>
#include <functional>
#include <iostream>
#include <chrono>

// Function to demonstrate simple thread execution
void simple_task() {
    std::cout << "Simple task running in thread\n";
}

// Function to demonstrate passing arguments by reference
void increment_vector(std::vector<int>& v) {
    for (auto& x : v) x++;
}

// Function to demonstrate heartbeat
void heartbeat() {
    while (true) {
        std::cout << "Heartbeat: " << std::chrono::steady_clock::now().time_since_epoch().count() << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    // 1. Simple thread execution
    std::thread t1(simple_task);
    t1.join();

    // 2. Passing arguments to threads
    std::vector<int> data = {1, 2, 3};
    std::thread t2(increment_vector, std::ref(data));
    t2.join();
    for (const auto& x : data) std::cout << x << " "; // Output: 2 3 4
    std::cout << '\n';

    // 3. Using thread identifiers
    std::thread t3(simple_task);
    if (t3.joinable()) {
        std::cout << "Thread t3 ID: " << t3.get_id() << '\n';
        t3.join();
    }

    // 4. Moving threads into a vector
    std::vector<std::thread> workers(3);
    for (int i = 0; i < 3; ++i) {
        workers[i] = std::thread([](int id) { std::cout << "Worker " << id << " running\n"; }, i);
    }
    for (auto& t : workers) t.join();

    // 5. Heartbeat (commented to avoid infinite loop)
    // std::thread t4(heartbeat);
    // t4.detach(); // Let the thread run independently

    return 0;
}
