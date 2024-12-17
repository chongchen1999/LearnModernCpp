#include <iostream>

class Date {
public:
    int day, month, year;

    // Default Constructor
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {
        std::cout << "Constructor called\n";
    }

    // Display Function
    void display() const {
        std::cout << day << "/" << month << "/" << year << "\n";
    }
};

int main() {
    // Default construction
    Date my_birthday(30, 12, 1995);
    std::cout << "My Birthday: ";
    my_birthday.display();

    // Default Copy Initialization
    Date d1 = my_birthday;  // Calls the default copy constructor
    std::cout << "Copy of my_birthday (d1): ";
    d1.display();

    Date d2 {my_birthday};  // Also copy initialization
    std::cout << "Copy of my_birthday (d2): ";
    d2.display();

    // Copy Assignment
    Date another_date;
    another_date = my_birthday;  // Calls the default copy assignment operator
    std::cout << "Assigned another_date: ";
    another_date.display();

    return 0;
}
