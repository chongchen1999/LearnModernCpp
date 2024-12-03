#include <iostream>
#include <cstring>
#include <chrono>

void cpy(char* dest, const char* src) {
    while (*dest++ = *src++) {}
}

int main() {
    const char* src = "This is a test string to compare performance between custom cpy and std::strcpy";
    constexpr size_t size = 1024; // Assume a reasonably large size for the buffer
    char dest1[size];
    char dest2[size];
    constexpr int iterations = 1000000; // Number of iterations to test performance

    // Measure time for custom cpy
    auto start_cpy = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        cpy(dest1, src);
    }
    auto end_cpy = std::chrono::high_resolution_clock::now();

    // Measure time for std::strcpy
    auto start_strcpy = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        std::strcpy(dest2, src);
    }
    auto end_strcpy = std::chrono::high_resolution_clock::now();

    // Calculate durations
    auto duration_cpy = std::chrono::duration_cast<std::chrono::microseconds>(end_cpy - start_cpy).count();
    auto duration_strcpy = std::chrono::duration_cast<std::chrono::microseconds>(end_strcpy - start_strcpy).count();

    // Output results
    std::cout << "Custom cpy duration: " << duration_cpy << " microseconds\n";
    std::cout << "std::strcpy duration: " << duration_strcpy << " microseconds\n";

    if (std::strcmp(dest1, dest2) == 0) {
        std::cout << "Both methods produce identical results.\n";
    } else {
        std::cout << "The results differ!\n";
    }

    return 0;
}
