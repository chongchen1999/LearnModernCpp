#include <stack>
#include <queue>
#include <vector>
#include <iostream>

// Example for stack
void stack_example() {
    std::stack<int> s1;
    std::stack<int, std::vector<int>> s2;

    s1.push(10);
    s1.push(20);
    std::cout << "Top element in stack: " << s1.top() << "\n";
    s1.pop();
    std::cout << "Top element after pop: " << s1.top() << "\n";
}

// Example for queue
void queue_example() {
    std::queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);

    while (!q.empty()) {
        std::cout << "Front element in queue: " << q.front() << "\n";
        q.pop();
    }
}

// Example for priority_queue
void priority_queue_example() {
    struct Compare {
        bool operator()(int a, int b) {
            return a > b; // Min-heap
        }
    };

    std::priority_queue<int> pq;
    std::priority_queue<int, std::vector<int>, Compare> min_pq;

    pq.push(30);
    pq.push(10);
    pq.push(20);

    std::cout << "Max-heap:\n";
    while (!pq.empty()) {
        std::cout << pq.top() << "\n";
        pq.pop();
    }

    min_pq.push(30);
    min_pq.push(10);
    min_pq.push(20);

    std::cout << "Min-heap:\n";
    while (!min_pq.empty()) {
        std::cout << min_pq.top() << "\n";
        min_pq.pop();
    }
}

int main() {
    std::cout << "Stack Example:\n";
    stack_example();
    std::cout << "\nQueue Example:\n";
    queue_example();
    std::cout << "\nPriority Queue Example:\n";
    priority_queue_example();
    return 0;
}
