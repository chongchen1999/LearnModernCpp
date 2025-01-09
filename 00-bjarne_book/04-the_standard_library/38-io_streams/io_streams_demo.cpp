// io_streams_demo.cpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Demonstrates file streams
void file_test() {
    std::ofstream ofs("example.txt"); // Open for writing
    if (!ofs) {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }
    ofs << "Hello, file!\n";
    ofs.close();

    std::ifstream ifs("example.txt"); // Open for reading
    if (!ifs) {
        std::cerr << "Failed to open file for reading.\n";
        return;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << "Read from file: " << line << '\n';
    }
}

// Demonstrates string streams
void string_test() {
    std::ostringstream oss("Label: ", std::ios::ate); // Write at end
    oss << "val";
    std::cout << "Output: " << oss.str() << '\n'; // Output: Label: val

    std::istringstream iss("Foobar"); // Read from string
    std::string word;
    iss >> word;
    std::cout << "Read: " << word << '\n'; // Output: Foobar
}

// Demonstrates stream state handling
void state_test() {
    std::istringstream iss("123 abc");
    int num;
    iss >> num; // Reads 123
    if (iss) {
        std::cout << "First read successful: " << num << '\n';
    }

    iss >> num; // Fails (abc cannot be converted to int)
    if (!iss) {
        std::cerr << "Second read failed.\n";
    }
}

int main() {
    std::cout << "File Test:\n";
    file_test();

    std::cout << "\nString Test:\n";
    string_test();

    std::cout << "\nState Test:\n";
    state_test();

    return 0;
}
