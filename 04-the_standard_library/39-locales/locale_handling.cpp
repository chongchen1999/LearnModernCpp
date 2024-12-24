#include <iostream>
#include <locale>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

class Date {
private:
    int dayVal;
    int monthVal;
    int yearVal;
public:
    Date(int d = 3, int m = 3, int y = 2000) : dayVal(d), monthVal(m), yearVal(y) {}
    int day() const { return dayVal; }
    int month() const { return monthVal; }
    int year() const { return yearVal; }
    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d.year() << "-" << d.month() << "-" << d.day();
        return os;
    }
    friend istream& operator>>(istream& is, Date& d) {
        char dash1, dash2;
        is >> d.yearVal >> dash1 >> d.monthVal >> dash2 >> d.dayVal;
        if (!is || dash1!= '-' || dash2!= '-') {
            is.setstate(ios::failbit);
        }
        return is;
    }
};

void print_date(const Date& d, int where_am_I) {
    std::ostringstream oss;
    std::tm tm = {};
    tm.tm_mday = d.day();
    tm.tm_mon = d.month() - 1;
    tm.tm_year = d.year() - 1900;
    switch (where_am_I) {
    case 1: // DK: Danish format
        oss.imbue(locale{"da_DK.UTF - 8"});
        oss << std::put_time(&tm, "%d. %B %Y");
        break;
    case 2: // ISO: ISO format
        oss << d;
        break;
    case 3: // US: US format
        oss.imbue(locale{"en_US.UTF - 8"});
        oss << std::put_time(&tm, "%m/%d/%Y");
        break;
    }
    std::cout << oss.str();
}

void cpy(istream& is, ostream& os) {
    Date d;
    double volume;
    while (is >> d >> volume) {
        os << d << ' ' << volume << '\n';
    }
    if (is.eof()) {
        is.clear();
    } else {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void f(istream& fin, ostream& fout, istream& fin2, ostream& fout2) {
    try {
        fin.imbue(std::locale("en_US.UTF - 8"));
        fout.imbue(std::locale("fr_FR.UTF - 8"));
        cpy(fin, fout);

        fin2.imbue(std::locale("fr_FR.UTF - 8"));
        fout2.imbue(std::locale("en_US.UTF - 8"));
        cpy(fin2, fout2);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error setting locale: " << e.what() << std::endl;
    }
}

int main() {
    std::stringstream input1("1999 - 04 - 12 10.5");
    std::stringstream output1;
    std::stringstream input2("12/04/1999 20.3");
    std::stringstream output2;
    f(input1, output1, input2, output2);
    return 0;
}