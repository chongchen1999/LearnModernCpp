#include <iostream>
#include <vector>
#include <string>

using namespace std;

// A simple Link structure
template <typename T>
struct Link {
    Link* pre;     // Pointer to the previous link
    Link* suc;     // Pointer to the next link
    T val;         // Value stored in the link
};

// A List template
template <typename T>
class List {
    Link<T>* head; // Pointer to the first link

public:
    List() : head{nullptr} {} // Default constructor
    void add(const T& value) {
        head = new Link<T>{nullptr, head, value}; // Add a value
    }

    void print_all() const {
        for (Link<T>* p = head; p; p = p->suc) {
            cout << p->val << " "; // Requires T to support << operator
        }
        cout << endl;
    }
};

// Usage example
class Rec {
    string name;
    string address;

public:
    friend ostream& operator<<(ostream& os, const Rec& r) {
        os << "Name: " << r.name << ", Address: " << r.address;
        return os;
    }
};

void f(const List<int>& li, const List<Rec>& lr) {
    li.print_all(); // OK, int supports << operator
    lr.print_all(); // OK, Rec supports << operator with a custom friend
}

int main() {
    // Integer list
    List<int> intList;
    intList.add(1);
    intList.add(2);

    // Record list
    List<Rec> recList;

    // Call function
    f(intList, recList);

    return 0;
}
