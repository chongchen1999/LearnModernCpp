#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <iostream>
#include <random>
#include <thread>

// Demonstrating various standard library headers and their usage
int main() {
    // Containers: Vector example
    std::vector<int> v = {1, 2, 3};
    v.push_back(4);  // Add an element
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;

    // General Utilities: Pair example
    std::pair<int, std::string> p = {1, "apple"};
    std::cout << p.first << " " << p.second << std::endl;

    // Algorithms: Sort example
    std::vector<int> unsorted = {4, 1, 3, 2};
    std::sort(unsorted.begin(), unsorted.end());
    for (int x : unsorted) std::cout << x << " ";
    std::cout << std::endl;

    // Diagnostics: Exception handling
    try {
        throw std::runtime_error("An error occurred!");
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    // Strings: String example
    std::string s = "Hello, World!";
    std::cout << s << std::endl;

    // I/O: Basic example
    std::cout << "Enter a number: ";
    int x;
    std::cin >> x;
    std::cout << "You entered: " << x << std::endl;

    // Numerics: Random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    std::cout << "Random number: " << dis(gen) << std::endl;

    // Concurrency: Threads
    std::thread t([]() {
        std::cout << "Hello from a thread!" << std::endl;
    });
    t.join();

    return 0;
}
