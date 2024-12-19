#include <iostream>
#include <string>

using namespace std;

namespace Chrono {

// Enum class to represent months
enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

// Helper functions
bool is_date(int d, Month m, int y); // Checks if the date is valid
bool is_leapyear(int y);             // Checks for leap year

// Date Class
class Date {
public:
    // Exception class for invalid dates
    class Bad_date { };

    // Constructor
    explicit Date(int dd = {}, Month mm = {}, int yy = {}) 
        : d{dd}, m{int(mm)}, y{yy} {
        if (!is_valid()) throw Bad_date();
    }

    // Non-modifying functions for examining the Date
    int day() const { return d; }
    Month month() const { return Month(m); }
    int year() const { return y; }

    string string_rep() const;          // Return string representation
    void char_rep(char s[], int max) const; // C-style representation

    // Modifying functions
    Date& add_day(int n);
    Date& add_month(int n);
    Date& add_year(int n);

private:
    int d, m, y; // Representation: day, month, year
    bool is_valid(); // Validates the date
};

bool Date::is_valid() {
    return is_date(d, Month(m), y);
}

// Helper function definitions
bool is_date(int d, Month m, int y) {
    if (y < 1 || d < 1) return false;

    int days_in_month = 31; // Default for most months
    switch (m) {
        case Month::feb:
            days_in_month = is_leapyear(y) ? 29 : 28;
            break;
        case Month::apr: case Month::jun: case Month::sep: case Month::nov:
            days_in_month = 30;
            break;
        default:
            break;
    }
    return d <= days_in_month;
}

bool is_leapyear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Modifying functions implementation
Date& Date::add_day(int n) {
    d += n;
    while (!is_valid()) {
        if (m == 12) { m = 1; ++y; }
        else ++m;
        d -= 31; // Simplified adjustment
    }
    return *this;
}

Date& Date::add_month(int n) {
    m += n;
    while (m > 12) { m -= 12; ++y; }
    if (!is_valid()) d = 1; // Reset day if invalid
    return *this;
}

Date& Date::add_year(int n) {
    y += n;
    if (m == int(Month::feb) && d == 29 && !is_leapyear(y)) d = 28;
    return *this;
}

// Output operator overload
ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.day() << ',' << int(d.month()) << ',' << d.year() << ')';
}

// Input operator overload
istream& operator>>(istream& is, Date& d) {
    int dd, mm, yy;
    char ch1, ch2, ch3;
    is >> ch1 >> dd >> ch2 >> mm >> ch3 >> yy;
    if (!is || ch1 != '(' || ch2 != ',' || ch3 != ',' || ch3 != ')') {
        is.clear(ios_base::failbit);
        return is;
    }
    d = Date(dd, Month(mm), yy);
    return is;
}

// Default date function
const Date& default_date() {
    static const Date dd{1, Month::jan, 1970};
    return dd;
}

} // End of namespace Chrono

// Test function
int main() {
    using namespace Chrono;

    try {
        Date d{16, Month::dec, 2024}; // Create a date
        cout << "Date: " << d << '\n';

        auto &d2 = d.add_day(1);
        cout << "After adding a day: " << d << '\n';
        cout << &d << ' ' << &d2 << '\n';

        Date default_d;
        cout << "Default Date: " << default_d << '\n';
    }
    catch (Date::Bad_date) {
        cerr << "Invalid date provided.\n";
    }

    return 0;
}
