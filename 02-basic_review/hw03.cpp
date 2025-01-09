#include <cmath>
#include <cstdint>  // For int32_t and uint32_t
#include <iomanip>
#include <iostream>

float GetInvSqrt(float num) {
    int32_t i;
    float y;

    // Bit-level manipulation
    i = *reinterpret_cast<int32_t*>(&num);  // Interpret float as int32_t
    i = 0x5f3759df - (i >> 1);              // Magic number and bit shift
    y = *reinterpret_cast<float*>(&i);      // Convert back to float

    // Newton's iteration
    y = y * (1.5f - (num * 0.5f * y * y));
    return y;
}

int main() {
    // Test the GetInvSqrt function
    float numbers[] = {1.0f, 2.0f, 4.0f, 10.0f, 100.0f};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Number\tInvSqrt\t\t1/sqrt\t\tError\n";

    for (size_t i = 0; i < n; ++i) {
        float num = numbers[i];
        float invSqrt = GetInvSqrt(num);
        float trueInvSqrt = 1.0f / std::sqrt(num);
        float error = std::fabs(invSqrt - trueInvSqrt);

        std::cout << num << "\t" << invSqrt << "\t" << trueInvSqrt << "\t"
                  << error << "\n";
    }

    return 0;
}
