#include <iostream>
#include <functional> // For std::plus and std::multiplies

// Node structure for a singly linked list
struct Node {
    Node* next;
    int data;
};

// Custom iterator for Node
class NodeIterator {
    Node* current;

public:
    explicit NodeIterator(Node* node) : current(node) {}

    // Overload dereference operator
    int operator*() const { return current->data; }

    // Overload pre-increment operator
    NodeIterator& operator++() {
        current = current->next;
        return *this;
    }

    NodeIterator operator++(int) {
        NodeIterator temp = *this;
        current = current->next;
        return temp;
    }

    // Overload equality comparison
    bool operator!=(const NodeIterator& other) const { return current != other.current; }
};

// Sum function: Generalized version for iterators
template<typename Iter, typename Val>
Val sum(Iter first, Iter last) {
    Val s = 0;
    while (first != last) {
        s += *first;
        ++first;
    }
    return s;
}

// Accumulate function: Generalized for custom operations
template<typename Iter, typename Val, typename Oper>
Val accumulate(Iter first, Iter last, Val s, Oper op) {
    while (first != last) {
        s = op(s, *first);
        ++first;
    }
    return s;
}

// Test cases
int main() {
    // Test sum with an array
    double ad[] = {1, 2, 3, 4};
    double sum_result = sum<double*, double>(ad, ad + 4);
    std::cout << "Sum of array: " << sum_result << "\n";

    // Test accumulate with addition
    double acc_sum = accumulate(ad, ad + 4, 0.0, std::plus<double>());
    std::cout << "Accumulate sum: " << acc_sum << "\n";

    // Test accumulate with multiplication
    double acc_product = accumulate(ad, ad + 4, 1.0, std::multiplies<double>());
    std::cout << "Accumulate product: " << acc_product << "\n";

    // Test sum with a linked list
    Node n3{nullptr, 3}, n2{&n3, 2}, n1{&n2, 1};
    NodeIterator first(&n1);
    NodeIterator last(nullptr);
    int list_sum = sum<NodeIterator, int>(first, last);
    std::cout << "Sum of linked list: " << list_sum << "\n";

    // Test accumulate with a linked list
    int acc_list_sum = accumulate(first, last, 0, std::plus<int>());
    std::cout << "Accumulate sum (list): " << acc_list_sum << "\n";

    return 0;
}
