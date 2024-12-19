#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <omp.h>

// SumOp: Reduction operation for summing values
template <typename T>
struct SumOp {
    static const T identity;
    T operator()(const T &a, const T &b) const {
        return a + b;
    }
};

template <typename T>
const T SumOp<T>::identity = static_cast<T>(0);

// CPU-based reduction
template <typename T, class ReductionOp = SumOp<T>>
T cpuReduce(T *data, int N) {
    T result = ReductionOp::identity;
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < N; ++i) {
        result = ReductionOp(result, data[i]);
    }
    return result;
}

int main() {
    const int N = 8192;
    const int iterations = 1000;

    std::srand(233u);

    // Allocate and initialize data
    std::vector<float> host_data(N);
    float cpu_sum = 0.f;
    std::generate(host_data.begin(), host_data.end(), []() { return static_cast<float>(rand()) / RAND_MAX; });
    for (const auto &val : host_data) {
        cpu_sum += val;
    }
    std::cout << "cpu sum (sequential): " << cpu_sum << std::endl;

    // Multi-threaded reduction using OpenMP
    float cpu_parallel_sum = 0.f;

    double start_time = omp_get_wtime();
    for (int i = 0; i < iterations; ++i) {
        cpu_parallel_sum = 0.f; // Reset for each iteration

        #pragma omp parallel for reduction(+:cpu_parallel_sum)
        for (int j = 0; j < N; ++j) {
            cpu_parallel_sum += host_data[j];
        }
    }
    double end_time = omp_get_wtime();

    double avg_time_ms = (end_time - start_time) * 1000.0 / iterations;
    printf("Time: %f ms\n", avg_time_ms);

    std::cout << std::fixed << std::setprecision(4); // Set fixed-point notation and precision
    std::cout << "cpu result (parallel): " << cpu_parallel_sum << std::endl;

    return 0;
}
