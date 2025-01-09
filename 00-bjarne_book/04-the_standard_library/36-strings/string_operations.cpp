#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <algorithm>


// String vs C - Style Strings example functions
std::string address(const std::string& identifier, const std::string& domain) {
    return identifier + '@' + domain;
}

char* address_c_style(const char* identifier, const char* domain) {
    int iden_len = strlen(identifier);
    int dom_len = strlen(domain);
    char* addr = (char*)malloc(iden_len + dom_len + 2);
    strcpy(addr, identifier);
    addr[iden_len] = '@';
    strcpy(addr + iden_len + 1, domain);
    return addr;
}


// Constructors example
void constructor_example() {
    std::string s0;
    std::string s1{"As simple as that!"};
    std::string s2{s1};
    std::string s3{7, 'a'};
}


// Fundamental Operations example
void fill(std::istream& in, std::string& s, int max) {
    s.reserve(max);
    in.read(&s[0], max);
    const int n = in.gcount();
    s.resize(n);
    s.shrink_to_fit();
}


// String I/O example
void string_io_example() {
    std::vector<std::string> lines;
    for (std::string s; std::getline(std::cin, s);) {
        lines.push_back(s);
    }
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
}


// Numeric Conversions example
void numeric_conversions_example() {
    std::string s = "123.45";
    auto x1 = std::stoi(s);
    auto x2 = std::stod(s);
    std::cout << "x1: " << x1 << ", x2: " << x2 << std::endl;
}


// STL - like Operations example
void add_middle(std::string& s, const std::string& middle) {
    auto p = s.find(' ');
    s.insert(p, " " + middle);
}


// The find Family example
void find_family_example() {
    std::string s{"accdcde"};
    auto i1 = s.find("cd");
    auto i2 = s.rfind("cd");
    auto i3 = s.find_first_of("cd");
    std::cout << "find \"cd\": " << i1 << ", rfind \"cd\": " << i2 << ", find_first_of \"cd\": " << i3 << std::endl;
}


// Substrings example
void substrings_example() {
    std::string s = "Mary had a little lamb";
    std::string s2 = s.substr(0, 4);
    auto i1 = s.compare(s2);
    auto i2 = s.compare(0, 4, s2);
    std::cout << "compare s and s2: " << i1 << ", compare part of s and s2: " << i2 << std::endl;
}


int main() {
    // String vs C - Style Strings
    std::string t = address("bs", "somewhere");
    std::cout << "C++ string address: " << t << std::endl;
    char* t_c_style = address_c_style("bs", "somewhere");
    std::cout << "C - style string address: " << t_c_style << std::endl;
    free(t_c_style);

    // Constructors
    constructor_example();

    // Fundamental Operations
    std::string s;
    fill(std::cin, s, 100);
    std::cout << "Size: " << s.size() << ", Capacity: " << s.capacity() << std::endl;

    // String I/O
    string_io_example();

    // Numeric Conversions
    numeric_conversions_example();

    // STL - like Operations
    std::string dmr = "Dennis Ritchie";
    add_middle(dmr, "MacAlistair");
    std::cout << dmr << std::endl;

    // The find Family
    find_family_example();

    // Substrings
    substrings_example();

    return 0;
}
