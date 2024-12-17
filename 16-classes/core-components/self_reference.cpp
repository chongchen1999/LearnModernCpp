#include <iostream>
using namespace std;

// Linked list example
struct Link {
    Link* pre;
    Link* suc;
    int data;

    Link(int d) : pre(nullptr), suc(nullptr), data(d) {}
    Link(Link* p, Link* s, int d) : pre(p), suc(s), data(d) {}

    Link* insert(int x) { // Insert x before this
        Link* new_link = new Link{pre, this, x};
        if (pre) pre->suc = new_link;
        pre = new_link;
        return new_link;
    }

    void remove() { // Remove and destroy this node
        if (pre) pre->suc = suc;
        if (suc) suc->pre = pre;
        delete this;
    }

    ~Link() {
        // Recursively delete the entire list
        if (suc) delete suc;
    }
};

int main() {
    Link* head = new Link(10);
    head->insert(5); // Insert before head
    head->remove();  // Remove head
    // delete head; // This is incorrect because head is already deleted

    return 0;
}