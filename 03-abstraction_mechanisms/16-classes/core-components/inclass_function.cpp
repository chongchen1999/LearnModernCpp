#include <iostream>
using namespace std;

class Date {
    int d{1}; // Default day
    int m{1}; // Default month
    int y{2000}; // Default year

public:
    // In-class function definition
    void add_month(int n) { 
        m += n; // Increment the month
        if (m > 12) { 
            y += (m - 1) / 12; // Increment year
            m = (m - 1) % 12 + 1; // Wrap around months
        }
    }

    // Inline function definition outside the class
    void display() const;

    // Getter for the year (example of a very small function)
    int get_year() const { return y; } // In-class definition
};

// Member function definition outside the class
inline void Date::display() const {
    cout << "Date: " << d << "/" << m << "/" << y << "\n";
}

// Main function to demonstrate in-class and out-of-class function definitions
int main() {
    Date date;
    date.display(); // Output: Date: 1/1/2000

    date.add_month(14); // Adds 14 months
    date.display(); // Output: Date: 1/3/2001

    cout << "Year: " << date.get_year() << "\n"; // Output: Year: 2001

    return 0;
}
