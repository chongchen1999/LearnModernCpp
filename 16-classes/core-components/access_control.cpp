#include <iostream>

class Date {
    int d, m, y; // Private data members

public:
    // Public member functions
    void init(int dd, int mm, int yy) {
        if (dd <= 0 || mm <= 0 || mm > 12 || yy < 0) {
            std::cerr << "Invalid date\n";
            return;
        }
        d = dd;
        m = mm;
        y = yy;
    }

    void add_year(int n) {
        y += n; // Add n years
    }

    void add_month(int n) {
        m += n;
        while (m > 12) { // Adjust year if months exceed 12
            m -= 12;
            y++;
        }
    }

    void add_day(int n) {
        d += n;
        // Simplistic handling of days, assuming all months have 30 days
        while (d > 30) {
            d -= 30;
            add_month(1); // Adjust month
        }
    }

    // Function to display the date
    void display() const {
        std::cout << d << "/" << m << "/" << y << "\n";
    }
};

// Non-member function trying to access private data
void timewarp(Date& d) {
    // d.y -= 200; // ERROR: y is private
    std::cerr << "Cannot directly modify private members of Date.\n";
}

int main() {
    Date dx;

    // Initialize the date
    dx.init(25, 3, 2011); // Valid initialization
    dx.display();         // Output: 25/3/2011

    // Add years, months, and days
    dx.add_year(10);      // Adds 10 years
    dx.display();         // Output: 25/3/2021

    dx.add_month(15);     // Adds 15 months (adjusts to 3 years, 3 months)
    dx.display();         // Output: 25/6/2022

    dx.add_day(40);       // Adds 40 days (adjusts to 1 month, 10 days)
    dx.display();         // Output: 5/8/2022

    // Attempt to misuse private members (this will fail)
    timewarp(dx);

    return 0;
}
