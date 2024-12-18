#include <iostream>
#include <vector>
#include <string>
#include <utility> // for std::pair

using namespace std;

// Associative array class
struct Assoc {
    vector<pair<string, int>> vec; // Vector of {name, value} pairs

    // Const operator[]: Read-only access
    const int& operator[](const string& s) const {
        for (const auto& x : vec) {
            if (s == x.first) {
                return x.second; // Return value if key is found
            }
        }
        throw out_of_range("Key not found"); // Throw exception if key not found
    }

    // Non-const operator[]: Read and modify access
    int& operator[](const string& s) {
        for (auto& x : vec) {
            if (s == x.first) {
                return x.second; // Return reference to value if key is found
            }
        }
        vec.push_back({s, 0}); // Add new pair {key, 0} if key not found
        return vec.back().second; // Return reference to the value
    }
};

int main() {
    Assoc values;
    string buf;

    // Count occurrences of each word from input
    while (cin >> buf) {
        ++values[buf]; // Increment count for the word
    }

    // Print all key-value pairs
    for (const auto& x : values.vec) {
        cout << '{' << x.first << ',' << x.second << "}\n";
    }

    return 0;
}
