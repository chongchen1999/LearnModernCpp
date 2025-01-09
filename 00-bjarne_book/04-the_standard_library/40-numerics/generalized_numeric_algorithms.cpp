#include <iostream>
#include <vector>
#include <numeric>  // For accumulate, inner_product, partial_sum, adjacent_difference, iota
#include <functional> // For std::multiplies

int main() {
    // Example vector
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 1. accumulate: Sum and product of elements
    int sum = std::accumulate(vec.begin(), vec.end(), 0); // Sum: 15
    int product = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<>()); // Product: 120

    // 2. inner_product: Dot product of two sequences
    std::vector<int> vec2 = {5, 4, 3, 2, 1};
    int dot_product = std::inner_product(vec.begin(), vec.end(), vec2.begin(), 0); // Dot Product: 35

    // 3. partial_sum: Cumulative sum
    std::vector<int> cumulative(vec.size());
    std::partial_sum(vec.begin(), vec.end(), cumulative.begin()); // {1, 3, 6, 10, 15}

    // 4. adjacent_difference: Differences between adjacent elements
    std::vector<int> differences(vec.size());
    std::adjacent_difference(vec.begin(), vec.end(), differences.begin()); // {1, 1, 1, 1, 1}

    // 5. iota: Fill with consecutive values
    std::vector<int> sequence(5);
    std::iota(sequence.begin(), sequence.end(), 10); // {10, 11, 12, 13, 14}

    // Output results
    std::cout << "Original vector: ";
    for (int v : vec) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "Sum: " << sum << "\n";
    std::cout << "Product: " << product << "\n";
    std::cout << "Dot product with {5, 4, 3, 2, 1}: " << dot_product << "\n";

    std::cout << "Cumulative sum: ";
    for (int v : cumulative) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "Adjacent differences: ";
    for (int v : differences) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "Sequence from iota (starting at 10): ";
    for (int v : sequence) std::cout << v << " ";
    std::cout << "\n";

    return 0;
}
