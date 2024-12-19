#include <iostream>
#include <string>
using namespace std;

// Simulating today's date for demonstration purposes
struct Today {
    int d = 16;
    int m = 12;
    int y = 2024;
} today;

// Date class with constructors
class Date {
    int d, m, y; // day, month, year

public:
    // Default constructor (sets to today's date)
    Date() : d(today.d), m(today.m), y(today.y) {}

    // Constructor with all arguments
    Date(int dd, int mm, int yy) : d(dd), m(mm), y(yy) {}

    // Constructor with day and month, using today's year
    Date(int dd, int mm) : d(dd), m(mm), y(today.y) {}

    // Constructor with only day, using today's month and year
    Date(int dd) : d(dd), m(today.m), y(today.y) {}

    // Constructor with a string date (e.g., "July 4, 1983")
    Date(const string& dateStr) {
        // For simplicity, this is a stub. Real parsing logic would go here.
        cout << "Parsing string date: " << dateStr << "\n";
        d = 1;
        m = 1;
        y = 2000;
    }

    // Display function for debugging
    void display() const {
        cout << "Date: " << d << "/" << m << "/" << y << "\n";
    }
};

// Main function to demonstrate constructors
int main() {
    // Using default constructor
    Date todayDate;
    todayDate.display(); // Output: Date: 16/12/2024

    // Using constructor with all arguments
    Date specificDate(25, 12, 2023);
    specificDate.display(); // Output: Date: 25/12/2023

    // Using constructor with day and month (default year = today.y)
    Date dayMonth(4, 7);
    dayMonth.display(); // Output: Date: 4/7/2024

    // Using constructor with only day (default month and year = today.m, today.y)
    Date dayOnly(15);
    dayOnly.display(); // Output: Date: 15/12/2024

    // Using constructor with a string
    Date fromString("July 4, 1983");
    fromString.display(); // Output: Parsing string date: July 4, 1983
                          // Date: 1/1/2000

    return 0;
}
