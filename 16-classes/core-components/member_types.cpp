#include <iostream>

// Template class with member types
template<typename T>
class Tree {
public:
    using value_type = T;               // Type alias for T
    enum Policy { rb, splay, treeps };  // Enum with tree policies

    // Nested class
    class Node {
        Node* right = nullptr;          // Pointer to the right child
        Node* left = nullptr;           // Pointer to the left child
        value_type value;               // Value of the node

    public:
        Node(value_type val) : value(val) {} // Constructor
        void f(Tree* p);                // Function accessing Tree
        value_type get_value() const { return value; } // Public getter
    };

private:
    Node* top = nullptr;                // Pointer to the root node

public:
    void g(const T&);                   // Function accessing Node
    void add_root(value_type val) { top = new Node(val); } // Add root
    Node* get_root() const { return top; } // Get root node
};

// Member function of nested class
template<typename T>
void Tree<T>::Node::f(Tree* p) {
    // p->top = right; // OK: Using a Tree pointer to access `top`
    if (p->top)
        std::cout << "Tree top value: " << p->top->value << "\n";
    else
        std::cout << "Tree is empty.\n";
}

// Member function of enclosing class
template<typename T>
void Tree<T>::g(const T&) {
    if (top)
        std::cout << "Root value: " << top->get_value() << "\n";
    else
        std::cout << "Tree is empty.\n";
}

// Test function
void test() {
    Tree<int> tree;                 // Tree of integers
    tree.add_root(10);              // Add root node
    tree.g(0);                      // Access root node
    Tree<int>::Node* root = tree.get_root(); // Get the root node
    if (root)
        root->f(&tree);             // Nested class function
}

int main() {
    test();
    return 0;
}
