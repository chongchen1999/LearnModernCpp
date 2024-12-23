#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <cctype>

// Sequence Containers Example
void sequence_containers_example() {
    std::vector<int> vec = {1, 2, 3};
    vec.push_back(4);

    std::list<int> lst = {1, 2, 3};
    lst.push_back(4);

    std::forward_list<int> fwd_lst = {1, 2, 3};
    fwd_lst.push_front(0);

    std::deque<int> dq = {1, 2, 3};
    dq.push_front(0);
    dq.push_back(4);

    std::cout << "Vector: ";
    for (int v : vec) std::cout << v << " ";
    std::cout << "\nList: ";
    for (int l : lst) std::cout << l << " ";
    std::cout << "\nForward List: ";
    for (int fl : fwd_lst) std::cout << fl << " ";
    std::cout << "\nDeque: ";
    for (int d : dq) std::cout << d << " ";
    std::cout << "\n";
}

// Associative Containers Example
void associative_containers_example() {
    std::map<std::string, int> word_count = {{"apple", 3}, {"banana", 2}};
    word_count["cherry"] = 5;

    std::set<int> unique_numbers = {1, 2, 3, 2, 1};

    std::cout << "Map: ";
    for (const auto& [key, value] : word_count) {
        std::cout << key << ":" << value << " ";
    }
    std::cout << "\nSet: ";
    for (int n : unique_numbers) std::cout << n << " ";
    std::cout << "\n";
}

// Container Adaptors Example
void container_adaptors_example() {
    std::stack<int> s;
    s.push(1);
    s.push(2);

    std::queue<int> q;
    q.push(1);
    q.push(2);

    std::priority_queue<int> pq;
    pq.push(10);
    pq.push(5);

    std::cout << "Stack top: " << s.top() << "\n";
    std::cout << "Queue front: " << q.front() << "\n";
    std::cout << "Priority Queue top: " << pq.top() << "\n";
}

// Custom Comparison Example
struct Nocase {
    bool operator()(const std::string& a, const std::string& b) const {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
            [](char x, char y) { return std::tolower(x) < std::tolower(y); });
    }
};

void custom_comparison_example() {
    std::vector<std::string> fruits = {"Apple", "pear", "Lemon"};
    std::sort(fruits.begin(), fruits.end(), Nocase());
    std::cout << "Sorted fruits: ";
    for (const auto& fruit : fruits) std::cout << fruit << " ";
    std::cout << "\n";
}

int main() {
    sequence_containers_example();
    associative_containers_example();
    container_adaptors_example();
    custom_comparison_example();
    return 0;
}
