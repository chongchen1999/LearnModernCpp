#include <iostream>

class Date {
    int d, m, y;                      // Non-static data members (per object)
    static Date default_date;         // Static data member shared across all objects

public:
    Date(int dd = 0, int mm = 0, int yy = 0); // Constructor with defaults
    static void set_default(int dd, int mm, int yy); // Set a new default date
    void print() const;               // Print the date for testing
};

// Static data member definition
Date Date::default_date{16, 12, 1770}; // Default date: Beethoven's birth date

// Constructor using static member
Date::Date(int dd, int mm, int yy) {
    d = dd ? dd : default_date.d;
    m = mm ? mm : default_date.m;
    y = yy ? yy : default_date.y;
    // Additional validation can be added here
}

// Static member function definition
void Date::set_default(int dd, int mm, int yy) {
    default_date = {dd, mm, yy};
}

// Member function to print a Date
void Date::print() const {
    std::cout << d << "/" << m << "/" << y << "\n";
}

// Test code
void test() {
    Date::set_default(4, 5, 1945); // Set new default date
    Date d1;                       // Default constructor
    d1.print();                    // Prints: 4/5/1945

    Date d2(10, 10, 2000);         // Constructor with values
    d2.print();                    // Prints: 10/10/2000

    Date d3(0, 11, 0);             // Partial default values
    d3.print();                    // Prints: 4/11/1945
}

int main() {
    test();
    return 0;
}
