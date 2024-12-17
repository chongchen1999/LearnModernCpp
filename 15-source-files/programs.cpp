#include <iostream>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <stdexcept>

// Global variables
double x = 2;         // Initialized to 2
double y;             // Initialized to 0
double sqx = sqrt(x); // Initialized after x

// Function that returns a static global variable
int& use_count() {
    static int count = 0;
    return count;
}

// Thread function
void thread_func() {
    std::cout << "y: " << y << ", x: " << x << "\n";
}

// Cleanup function for atexit
void cleanup() {
    std::cout << "Cleanup function executed\n";
}

// Cleanup function for quick_exit
void my_cleanup() {
    std::cout << "Cleanup using at_quick_exit\n";
}

int main(int argc, char* argv[]) {
    std::cout << "Program started\n";

    // Print program arguments
    std::cout << "Number of arguments: " << argc << "\n";
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << "\n";
    }

    // Global variable initialization
    std::cout << "x: " << x << ", y: " << y << ", sqx: " << sqx << "\n";

    // Static local variable
    std::cout << "Static count: " << ++use_count() << "\n";

    // Thread demonstration
    std::thread t1(thread_func);
    std::thread t2(thread_func);
    t1.join();
    t2.join();

    // atexit demonstration
    atexit(cleanup);

    // quick_exit demonstration
    std::at_quick_exit(my_cleanup);

    // Uncomment to demonstrate various terminations:
    // exit(0);                  // Terminate using exit()
    // abort();                  // Terminate using abort()
    // quick_exit(0);            // Terminate using quick_exit()
    // throw std::runtime_error("Unhandled exception!"); // Uncaught exception

    std::cout << "Program ending normally\n";
    return 0; // Normal termination
}
