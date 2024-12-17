#include <iostream>
#include <string>

struct Cache {
    bool valid = false;
    std::string rep;
};

class Date {
    int d, m, y; // day, month, year
    Cache* c;

    void compute_cache_value() const {
        c->rep = std::to_string(d) + "-" + std::to_string(m) + "-" + std::to_string(y);
        c->valid = true;
    }

public:
    Date(int day, int month, int year) 
        : d(day), m(month), y(year), c(new Cache()) {}

    ~Date() { delete c; }

    int day() const { return d; }
    int month() const { return m; }
    int year() const { return y; }

    void add_year(int n) { y += n; }

    std::string string_rep() const {
        if (!c->valid) {
            compute_cache_value();
        }
        return c->rep;
    }
};

// Example usage
int main() {
    Date today(16, 12, 2024);
    std::cout << "Today's date: " << today.string_rep() << "\n";

    today.add_year(1);
    std::cout << "Next year's date: " << today.string_rep() << "\n";

    const Date const_today(16, 12, 2024);
    std::cout << "Const Today's date: " << const_today.string_rep() << "\n";

    return 0;
}
