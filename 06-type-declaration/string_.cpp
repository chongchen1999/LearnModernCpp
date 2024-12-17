#include <iostream>
#include <string>

int main() {
    std::string s1 = "ababababbbbbbbbbbssssssssssbababbabababsssssssssssssssssssssssssssssssssssssssssssssssssab";
    std::string s2 = "a";

    std::cout << "sizeof(s1): " << sizeof(s1) << std::endl;  // Size of the string object itself
    std::cout << "sizeof(s2): " << sizeof(s2) << std::endl;  // Size of the string object itself

    return 0;
}
