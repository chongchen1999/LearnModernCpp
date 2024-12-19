#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

// Example function for basic pointer to function demonstration
void error(string s) {
    cout << "Error: " << s << endl;
}

void pointerToFunctionExample() {
    void (*efct)(string); // Pointer to function taking a string and returning nothing
    efct = &error;        // efct points to the error function

    (*efct)("Test Error");   // Call the error function through efct
    efct("Test Error");   // Call the error function through efct
    // both calls are equivalent

    std::cout << "address of void error(string): " << reinterpret_cast<void *>(efct) << std::endl;
    std::cout << "address of void error(string): " << reinterpret_cast<void *>(error) << std::endl;
    std::cout << "address of void error(string): " << reinterpret_cast<void *>(&error) << std::endl;
}

// Functions with different signatures
void f1(string s) { cout << "f1: " << s << endl; }
int f2(string s) { cout << "f2: " << s << endl; return 42; }
void f3(int* p) { cout << "f3: " << *p << endl; }

void pointerAssignmentExample() {
    void (*pf)(string); // Pointer to void(string)
    // typedef int (*PF)(string);
    using PF = int(*)(string);
    
    pf = &f1;  // OK
    pf("Hello"); // OK, calls f1

    PF pf2 = &f2;
    pf2("Hello");
    
    // pf = &f2; // Error: bad return type
    // pf = &f3; // Error: bad argument type
}

// Demonstrating pointer-to-function casting
using P1 = int(*)(int*);
using P2 = void(*)(void);

void castingExample(P1 pf) {
    std::cout << "address of int(*)(int*): " << reinterpret_cast<void *>(pf) << std::endl;
    P2 pf2 = reinterpret_cast<P2>(pf); // Convert to a different type
    // pf2(); // Dangerous: would likely crash or behave unpredictably

    P1 pf1 = reinterpret_cast<P1>(pf2); // Convert back
    int x = 7;
    int y = pf1(&x); // Works if used correctly
    cout << "y = " << y << endl;
}

// Example of sorting with function pointers
struct User {
    const char* name;
    const char* id;
    int dept;
};

int cmpByName(const void* p, const void* q) {
    return strcmp(static_cast<const User*>(p)->name, static_cast<const User*>(q)->name);
}

int cmpByDept(const void* p, const void* q) {
    return static_cast<const User*>(p)->dept - static_cast<const User*>(q)->dept;
}

void sortingExample() {
    vector<User> users = {
        {"Ritchie D.M.", "dmr", 11271},
        {"Sethi R.", "ravi", 11272},
        {"Szymanski T.G.", "tgs", 11273},
        {"Schryer N.L.", "nls", 11274},
        {"Kernighan B.W.", "bwk", 11276}
    };

    cout << "Original order:\n";
    for (const auto& user : users)
        cout << user.name << '\t' << user.id << '\t' << user.dept << '\n';

    // Sorting by name
    qsort(users.data(), users.size(), sizeof(User), cmpByName);
    cout << "\nSorted by name:\n";
    for (const auto& user : users)
        cout << user.name << '\t' << user.id << '\t' << user.dept << '\n';

    // Sorting by department
    qsort(users.data(), users.size(), sizeof(User), cmpByDept);
    cout << "\nSorted by department:\n";
    for (const auto& user : users)
        cout << user.name << '\t' << user.id << '\t' << user.dept << '\n';
}

// Modern C++ alternative using lambdas
void modernSortingExample() {
    vector<User> users = {
        {"Ritchie D.M.", "dmr", 11271},
        {"Sethi R.", "ravi", 11272},
        {"Szymanski T.G.", "tgs", 11273},
        {"Schryer N.L.", "nls", 11274},
        {"Kernighan B.W.", "bwk", 11276}
    };

    // Sorting using lambdas
    cout << "\nModern sorting by name:\n";
    sort(users.begin(), users.end(), [](const User& a, const User& b) {
        return strcmp(a.name, b.name) < 0;
    });
    for (const auto& user : users)
        cout << user.name << '\t' << user.id << '\t' << user.dept << '\n';

    cout << "\nModern sorting by department:\n";
    sort(users.begin(), users.end(), [](const User& a, const User& b) {
        return a.dept < b.dept;
    });
    for (const auto& user : users)
        cout << user.name << '\t' << user.id << '\t' << user.dept << '\n';
}

// Overloaded functions and noexcept pointers
void overloadedFunctionExample() {
    void f(int) noexcept;
    int f(char);
    
    void (*pf1)(int) noexcept = f; // OK
    // void (*pf2)(int) = f;        // Error: discards noexcept
    int (*pf3)(char) = f;          // OK
    cout << "Overloaded function example executed.\n";
    pf1(10);
    cout << pf3('a') << endl;
}

void f(int) noexcept {
    cout << "f(int) called.\n";
}
int f(char) {
    cout << "f(char) called.\n";
    return 0;
}

int main() {
    cout << "Pointer to Function Example:\n";
    pointerToFunctionExample();

    cout << "\nPointer Assignment Example:\n";
    pointerAssignmentExample();

    cout << "\nCasting Example:\n";
    P1 sampleFunction = [](int* x) -> int { return *x * 2; };
    std::cout << "address of sampleFunction: " << &sampleFunction << "\n";
    castingExample(sampleFunction);

    cout << "\nSorting Example:\n";
    sortingExample();

    cout << "\nModern Sorting Example:\n";
    modernSortingExample();

    cout << "\nOverloaded Function Example:\n";
    overloadedFunctionExample();

    return 0;
}
