#include <iostream>
#include <string>
using namespace std;

// Simulating today's date
struct Today {
    int d = 16;
    int m = 12;
    int y = 2024;
} today;

// Date class with in-class initializers
class Date {
    int d{today.d}; // Default to today's day
    int m{today.m}; // Default to today's month
    int y{today.y}; // Default to today's year

public:
    // Constructors
    Date(int day, int month, int year) : d{day}, m{month}, y{year} {}
    Date(int day, int month) : d{day}, m{month} {} // Uses today's year
    Date(int day) : d{day} {}                      // Uses today's month and year
    Date() {}                                      // Defaults to today
    Date(const char* dateString) {
        // Simplified parsing for example purposes
        string date = dateString;
        d = stoi(date.substr(0, 2)); // Extract day
        m = stoi(date.substr(3, 2)); // Extract month
        y = stoi(date.substr(6, 4)); // Extract year
    }

    // Display function for debugging
    void display() const {
        cout << "Date: " << d << "/" << m << "/" << y << "\n";
    }
};

// Main function to demonstrate in-class initializers
int main() {
    // Various ways to construct Date objects
    Date date1{25, 12, 2024}; // Explicit day, month, year
    Date date2{25, 12};       // Day and month, uses today's year
    Date date3{25};           // Day only, uses today's month and year
    Date date4;               // Default constructor, uses today's date
    Date date5{"01-01-2023"}; // From string representation

    // Display the dates
    date1.display(); // Output: Date: 25/12/2024
    date2.display(); // Output: Date: 25/12/2024
    date3.display(); // Output: Date: 25/12/2024
    date4.display(); // Output: Date: 16/12/2024
    date5.display(); // Output: Date: 1/1/2023

    return 0;
}
