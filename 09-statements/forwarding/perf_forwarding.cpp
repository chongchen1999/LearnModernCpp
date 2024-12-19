#include <iostream>
#include <string>

void print(std::string& s) {
    std::cout << "Lvalue: " << s << std::endl;
}

void print(std::string&& s) {
    std::cout << "Rvalue: " << s << std::endl;
}

template<typename T>
void wrapper(T&& arg) {
    print(std::forward<T>(arg)); // Preserves the value category
}

int main() {
    wrapper(std::string("Hello")); // Correctly moves the temporary string
    std::string str{"Hello"};
    wrapper(str);
    return 0;
}
