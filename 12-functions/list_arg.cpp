#include <iostream>
#include <initializer_list>
#include <string>
using namespace std;

template<class T>
void f1(initializer_list<T> il) {
    for (auto x : il) cout << x << " ";
    cout << endl;
}

struct S {
    int a;
    string s;
};

void f2(S s) {
    cout << "S: " << s.a << ", " << s.s << endl;
}

template<class T, int N>
void f3(T (&arr)[N]) {
    for (auto x : arr) cout << x << " ";
    cout << endl;
}

template<class T, int N>
void f3(T (&&arr)[N]) {
    for (auto x : arr) cout << x << " ";
    cout << endl;
}

void f4(int x) {
    cout << "f4: " << x << endl;
}

int main() {
    f1({1, 2, 3, 4});              // initializer_list<int>
    f2({1, "example"});            // S{1, "example"}
    int arr[] = {5, 6, 7, 8};
    std::cout << sizeof(arr) << std::endl;
    f3({5, 6, 7, 8});              // array<int, 4>
    f3(arr);
    f4({9});                       // f4(int{9})

    return 0;
}
