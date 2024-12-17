#include <iostream>
using namespace std;

// Using class: private by default
class Date1 {
    int d, m, y; // private by default

public:
    Date1(int dd, int mm, int yy) : d(dd), m(mm), y(yy) {}

    void add_year(int n) {
        y += n;
    }

    void display() const {
        cout << "Date1: " << d << "/" << m << "/" << y << "\n";
    }
};

// Using struct: public by default
struct Date2 {
private:
    int d, m, y; // private access explicitly declared

public:
    Date2(int dd, int mm, int yy) : d(dd), m(mm), y(yy) {}

    void add_year(int n) {
        y += n;
    }

    void display() const {
        cout << "Date2: " << d << "/" << m << "/" << y << "\n";
    }
};

// Alternative style: public first, private last
class Date3 {
public:
    Date3(int dd, int mm, int yy) : d(dd), m(mm), y(yy) {}

    void add_year(int n) {
        y += n;
    }

    void display() const {
        cout << "Date3: " << d << "/" << m << "/" << y << "\n";
    }

private:
    int d, m, y; // private members last
};

// Multiple access specifiers (not recommended in practice)
class Date4 {
public:
    Date4(int dd, int mm, int yy) : d(dd), m(mm), y(yy) {}

private:
    int d, m, y;

public:
    void add_year(int n) {
        y += n;
    }

    void display() const {
        cout << "Date4: " << d << "/" << m << "/" << y << "\n";
    }
};

int main() {
    // Using Date1 (class with private default)
    Date1 date1(25, 12, 2020);
    date1.add_year(1);
    date1.display(); // Output: Date1: 25/12/2021

    // Using Date2 (struct with explicit private members)
    Date2 date2(15, 6, 2015);
    date2.add_year(5);
    date2.display(); // Output: Date2: 15/6/2020

    // Using Date3 (class with public first)
    Date3 date3(1, 1, 2000);
    date3.add_year(22);
    date3.display(); // Output: Date3: 1/1/2022

    // Using Date4 (class with multiple access specifiers)
    Date4 date4(10, 10, 2010);
    date4.add_year(10);
    date4.display(); // Output: Date4: 10/10/2020

    return 0;
}
