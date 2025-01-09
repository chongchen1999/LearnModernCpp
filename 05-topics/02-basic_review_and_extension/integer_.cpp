#include <iostream>
#include <string>

int main() {
    std::string s = "hello, world!";
    size_t x = s.find("t");
    std::cout << (x != -1) << std::endl;
    return 0;
}