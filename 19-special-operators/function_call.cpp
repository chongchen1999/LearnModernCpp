#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <algorithm> // for std::for_each

// Class with function call operator
class Add {
    std::complex<double> val; // Store a complex value
public:
    Add(std::complex<double> c) : val{c} { }                 // Constructor with complex
    Add(double r, double i) : val{std::complex<double>(r, i)} { } // Constructor with real & imaginary
    void operator()(std::complex<double>& c) const { c += val; }   // Add stored value to argument
};

// Function using Add and std::for_each
void h(std::vector<std::complex<double>>& vec, std::list<std::complex<double>>& lst, std::complex<double> z) {
    std::for_each(vec.begin(), vec.end(), Add{2, 3}); // Adds (2, 3) to every vector element
    std::for_each(lst.begin(), lst.end(), Add{z});    // Adds z to every list element
}

// Function using lambda expressions
void h2(std::vector<std::complex<double>>& vec, std::list<std::complex<double>>& lst, std::complex<double> z) {
    std::for_each(vec.begin(), vec.end(), [](std::complex<double>& a) { a += std::complex<double>{2, 3}; }); // Add (2,3)
    std::for_each(lst.begin(), lst.end(), [&](std::complex<double>& a) { a += z; });    // Add z
}

// Main to demonstrate the functionality
int main() {
    std::vector<std::complex<double>> vec = {{1, 1}, {2, 2}, {3, 3}};
    std::list<std::complex<double>> lst = {{4, 4}, {5, 5}, {6, 6}};
    std::complex<double> z{1, 1};

    h(vec, lst, z); // Using Add class
    h2(vec, lst, z); // Using lambda expressions

    // Output results
    std::cout << "Vector after h and h2:\n";
    for (const auto& v : vec) std::cout << v << " ";
    std::cout << "\nList after h and h2:\n";
    for (const auto& l : lst) std::cout << l << " ";
    std::cout << std::endl;

    return 0;
}
