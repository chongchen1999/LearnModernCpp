#include <iostream>
#include <list>
#include <string>

using namespace std;

// Base class: Employee
class Employee {
public:
    // Constructor
    Employee(const string& first, const string& last, char middle, short dept)
        : first_name(first), family_name(last), middle_initial(middle), department(dept) {}

    // Print employee information
    virtual void print() const {
        cout << "Employee: " << full_name() << ", Department: " << department << '\n';
    }

    // Virtual destructor
    virtual ~Employee() {}

protected:
    // Helper function to get full name
    string full_name() const {
        return first_name + ' ' + middle_initial + ' ' + family_name;
    }

private:
    string first_name;
    string family_name;
    char middle_initial;
    short department;
};

// Derived class: Manager
class Manager : public Employee {
public:
    // Constructor
    Manager(const string& first, const string& last, char middle, short dept, short lvl)
        : Employee(first, last, middle, dept), level(lvl) {}

    // Add an employee to the group
    void add_to_group(Employee* emp) {
        group.push_back(emp);
    }

    // Override print function
    void print() const override {
        Employee::print(); // Print base class info
        cout << "Level: " << level << '\n';
        cout << "Manages: ";
        for (const auto& emp : group) {
            emp->print();
        }
    }

private:
    list<Employee*> group; // List of employees managed
    short level;           // Managerial level
};

// Main function demonstrating usage
int main() {
    // Create employees and managers
    Employee e1("John", "Doe", 'A', 101);
    Manager m1("Jane", "Smith", 'B', 102, 1);

    // Add employees to manager's group
    m1.add_to_group(&e1);

    // Print information
    e1.print();
    m1.print();

    return 0;
}
