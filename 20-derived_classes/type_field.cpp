#include <iostream>
#include <list>
#include <string>

struct Employee {
    std::string family_name;
    short department;

    Employee(const std::string& name = "", short dept = 0)
        : family_name(name), department(dept) {}

    virtual void print_info() const {
        std::cout << family_name << '\t' << department << '\n';
    }

    virtual ~Employee() = default;
};

struct Manager : public Employee {
    short level;

    Manager(const std::string& name = "", short dept = 0, short lvl = 0)
        : Employee(name, dept), level(lvl) {}

    void print_info() const override final {
        Employee::print_info();
        std::cout << " level " << level << '\n';
    }
};

// Function to print a list of employees
void print_list(const std::list<Employee*>& elist) {
    for (const auto& e : elist) {
        e->print_info();
    }
}

int main() {
    Manager m1("Smith", 101, 5);
    Employee e1("Johnson", 102);

    std::list<Employee*> employees = { &e1, &m1 };
    print_list(employees);

    return 0;
}
