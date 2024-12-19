#include <cstdlib>
#include <iostream>

[[noreturn]] void terminate_program() {
    std::cerr << "Terminating program.\n";
    std::exit(1); // Exits the program immediately
}

void example() {
    terminate_program(); 
    // Compiler knows the following code is unreachable
    std::cout << "This will never execute.\n";
}

int main() {
    example();
    // Compiler knows the following code is unreachable
    std::cout << "This will never execute.\n";
    return 0;
}