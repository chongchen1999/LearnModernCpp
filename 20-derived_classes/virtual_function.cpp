#include <iostream>
#include <list>
#include <string>

// Base class
class Employee {
public:
    Employee(const std::string& name, int dept)
        : family_name(name), department(dept) {}

    virtual void print() const { // Virtual function
        std::cout << family_name << '\t' << department << '\n';
    }

    virtual ~Employee() = default; // Virtual destructor for polymorphism

private:
    std::string family_name;
    short department;
};

// Derived class
class Manager : public Employee {
public:
    Manager(const std::string& name, int dept, int lvl)
        : Employee(name, dept), level(lvl) {}

    void print() const override { // Override base class virtual function
        Employee::print(); // Call base class print
        std::cout << "\tlevel " << level << '\n';
    }

private:
    short level;
};

// Function to print a list of employees
void print_list(const std::list<Employee*>& employees) {
    for (const auto& e : employees) {
        e->print(); // Calls the appropriate print function based on object type
    }
}

// Main function
int main() {
    Employee e("Brown", 1234);
    Manager m("Smith", 1234, 2);

    std::list<Employee*> employees = { &e, &m };
    print_list(employees);

    return 0;
}
