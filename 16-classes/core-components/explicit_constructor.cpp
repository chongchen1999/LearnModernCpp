#include <iostream>
using namespace std;

// Today's date simulation
struct Today {
    int d = 16;
    int m = 12;
    int y = 2024;
} today;

// Date class
class Date {
    int d, m, y; // day, month, year

public:
    // Explicit constructor with single argument
    explicit Date(int dd) : d(dd), m(today.m), y(today.y) {}

    // Explicit constructor with two arguments
    explicit Date(int dd, int mm) : d(dd), m(mm), y(today.y) {}

    // Explicit constructor with three arguments
    explicit Date(int dd, int mm, int yy) : d(dd), m(mm), y(yy) {}

    // Default constructor
    explicit Date() : d(today.d), m(today.m), y(today.y) {}

    // Display function for debugging
    void display() const {
        cout << "Date: " << d << "/" << m << "/" << y << "\n";
    }
};

// Demonstrating explicit constructors
int main() {
    // Explicit initialization
    Date date1{15};       // OK: Direct initialization
    Date date2 = Date{15}; // OK: Explicit conversion

    // Invalid cases (uncomment to see errors)
    // Date date3 = {15}; // Error: Implicit copy initialization not allowed
    // Date date4 = 15;   // Error: Implicit conversion not allowed

    // Using multi-argument explicit constructor
    Date date5{15, 11};       // OK: Direct initialization
    Date date6 = Date{15, 11}; // OK: Explicit conversion

    // Invalid case
    // Date date7 = {15, 11}; // Error: Implicit initialization not allowed

    // Default constructor
    Date todayDate; // OK: Explicit but default constructor
    todayDate.display(); // Output: Date: 16/12/2024

    // Passing explicit objects to functions
    auto my_fct = [](const Date& d) { d.display(); };

    my_fct(Date{1, 1, 2020}); // OK: Explicit conversion
    // my_fct(15);            // Error: Implicit conversion not allowed

    return 0;
}
