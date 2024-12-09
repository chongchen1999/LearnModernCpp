#include <cstdio> // Standard printf is in std::printf

void printf(int x) { // User-defined printf in the global namespace
    std::puts("This is my custom printf:");
}

int main() {
    printf("This is my custom printf.\n"); // Calls the user-defined function
    std::printf("This is std::printf.\n"); // Calls the standard library printf
    return 0;
}
