#include <iostream>
#include <vector>
#include <initializer_list>
#include <cstdarg>
#include <string>

using namespace std;

// [1] Variadic Template (Type-safe and modern)
template <typename... Args>
void error_template(int severity, Args... args) {
    cerr << "Variadic Template Error [Severity " << severity << "]: ";
    (cerr << ... << args) << '\n'; // Fold expression (C++17)
    if (severity) exit(severity);
}

// [2] Using std::initializer_list (Type-safe for homogeneous arguments)
void error_initializer_list(int severity, initializer_list<string> args) {
    cerr << "Initializer List Error [Severity " << severity << "]: ";
    for (const auto& arg : args) {
        cerr << arg << " ";
    }
    cerr << '\n';
    if (severity) exit(severity);
}

// [3] Using ellipsis (...) and <cstdarg> macros (Legacy and less safe)
void error_cstyle(int severity, ...) {
    cerr << "C-Style Error [Severity " << severity << "]: ";
    va_list args;
    va_start(args, severity); // Start processing variadic arguments
    
    while (true) {
        const char* arg = va_arg(args, const char*); // Expect char* arguments
        if (arg == nullptr) break;                  // Null pointer terminates the list
        cerr << arg << " ";
    }
    
    va_end(args); // Clean up
    cerr << '\n';
    if (severity) exit(severity);
}

int main() {
    // Inputs for demonstration
    const char* program_name = "my_program";
    const char* error_msg = "An error occurred";
    const char* hint = "Check your inputs";

    // [1] Variadic Template
    cout << "Using Variadic Template:\n";
    error_template(0, program_name, " - ", error_msg, " - ", hint);

    // [2] Initializer List
    cout << "\nUsing Initializer List:\n";
    error_initializer_list(0, {program_name, "-", error_msg, "-", hint});

    // [3] C-Style Variadic Function
    cout << "\nUsing C-Style Variadic Function:\n";
    error_cstyle(0, program_name, "-", error_msg, "-", hint, nullptr);

    return 0;
}
