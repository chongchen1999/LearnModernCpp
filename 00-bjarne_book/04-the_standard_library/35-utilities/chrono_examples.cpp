#include <chrono>
#include <iostream>
#include <type_traits>

using namespace std::chrono;
using namespace std;

// duration examples
void duration_examples() {
    // Define a duration of 7 milliseconds
    duration<long long, milli> d1{7};
    // Define a duration of 3.33 picoseconds
    duration<double, pico> d2{3.33};
    // Define a duration of 0 seconds
    duration<int, ratio<1, 1>> d3{};

    std::cout << "d1 count: " << d1.count() << '\n';
    std::cout << "d2 count: " << d2.count() << '\n';
    std::cout << "d3 count: " << d3.count() << '\n';

    // Assign d1 to d2
    d2 = d1;
    std::cout << "d1 count after assign: " << d1.count() << '\n';
    std::cout << "d2 count after assign: " << d2.count() << '\n';

    if (d1!= d2) std::cerr << "insane!";

    // Demonstrating narrowing initialization error
    // duration<int, milli> d{3.5}; // error: 3.5 to int is narrowing

    // Arithmetic operations on durations
    duration<long long, milli> d4{5};
    d1 += d4;
    std::cout << "d1 after addition: " << d1.count() << " milliseconds\n";

    // Using convenience aliases
    nanoseconds ns{1000};
    microseconds us = duration_cast<microseconds>(ns);
    std::cout << "1000 nanoseconds is " << us.count() << " microseconds\n";
}

void test() {
    time_point<steady_clock, milliseconds> tp1(milliseconds(100));
    time_point<steady_clock, microseconds> tp2(microseconds(100 * 1000));
    // tp1 = tp2; // error: would truncate
    tp2 = tp1;
    if (tp1!= tp2) std::cerr << "Insane!";
}

void test2() {
    auto tp = steady_clock::now();
    auto d1 = time_point_cast<hours>(tp).time_since_epoch().count() / 24;
    using days = duration<long, ratio<24 * 60 * 60, 1>>;
    auto d2 = time_point_cast<days>(tp).time_since_epoch().count();
    if (d1!= d2) std::cout << "Impossible!\n";
}

// time_point examples
void time_point_examples() {
    test();
    test2();
}

void test3() {
    auto t1 = system_clock::now();
    // Simulate some work
    for (int i = 0; i < 100000000; ++i);
    auto t2 = system_clock::now();
    std::cout << "Work took " << duration_cast<milliseconds>(t2 - t1).count() << " ms\n";
}

// clock examples
void clock_examples() {
    test3();
    std::cout << "min " << system_clock::duration::min().count()
              << ", max " << system_clock::duration::max().count()
              << ", " << (treat_as_floating_point<system_clock::duration>::value? "FP" : "integral") << '\n';
    std::cout << (system_clock::is_steady? "steady\n" : "not steady\n");
}

int main() {
    duration_examples();
    time_point_examples();
    clock_examples();
    return 0;
}