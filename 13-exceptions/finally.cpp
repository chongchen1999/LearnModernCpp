#include <iostream>
#include <cstdlib>
#include <memory>
using namespace std;

// Template for final actions
template <typename F>
struct Final_action {
    F clean;

    Final_action(F f) : clean{f} {}
    ~Final_action() {
        clean();
    }
};

// Helper function to create final actions
template <class F>
Final_action<F> finally(F f) {
    std::cout << typeid(F).name() << '\n';
    // std::cout << typeid(f).name() << '\n';
    return Final_action<F>(f);
}

void test() {
    // Dynamically allocate resources
    int* p = new int{7};
    int* buf = static_cast<int*>(malloc(100 * sizeof(int)));

    // Define cleanup actions with `finally`
    auto act1 = finally([&] {
        delete p;        // Clean up dynamic memory
        free(buf);       // Clean up C-style allocation
        cout << "Goodbye, Cruel world!\n";
    });
    std::cout << typeid(act1).name() << '\n';

    int var = 0;
    cout << "var = " << var << '\n';

    // Nested scope
    {
        var = 1;
        auto act2 = finally([&] {
            cout << "finally!\n";
            var = 7; // Modify variable as part of final action
        });
        cout << "var = " << var << '\n';
    } // act2 is executed here

    cout << "var = " << var << '\n';
} // act1 is executed here

int main() {
    test();
    return 0;
}
