#include <cstdarg>
#include <iostream>
using namespace std;

void error(int severity, ...) {
    va_list args;
    va_start(args, severity);

    while (true) {
        char* msg = va_arg(args, char*);
        if (!msg) break; // nullptr terminates the list
        cout << msg << " ";
    }

    va_end(args);
    cout << endl;
    if (severity) exit(severity);
}

int main() {
    error(1, "Error:", "Invalid input.", nullptr);
    return 0;
}
