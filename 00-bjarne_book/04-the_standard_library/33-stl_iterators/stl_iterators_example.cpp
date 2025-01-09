#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>

// Example 1
void example1() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = std::find(v.begin(), v.end(), 3);
    if (it!= v.end()) {
        std::cout << "Element found at position " << std::distance(v.begin(), it) << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }
}

template<typename Iter>
void forward(Iter p, int n) {
    while (n > 0)
        *p++ = --n;
}

// Example 2
void example2() {
    std::vector<int> v(10);
    forward(v.begin(), v.size());
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // forward(v.begin(), 1000); // This would cause trouble in some cases
}

// Example 3
void example3() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::list<int> l = {1, 2, 3, 4, 5};

    auto v_it = v.begin();
    v_it += 2; // Valid for random - access iterator
    std::cout << "Vector element at position 2: " << *v_it << std::endl;

    auto l_it = l.begin();
    // l_it += 2; // Error: bidirectional iterator doesn't support +=
    std::advance(l_it, 2);
    std::cout << "List element at position 2: " << *l_it << std::endl;
}

template<typename Iter>
void advance_helper(Iter p, int n, std::random_access_iterator_tag) {
    p += n;
}

template<typename Iter>
void advance_helper(Iter p, int n, std::forward_iterator_tag) {
    if (0 < n)
        while (n--) ++p;
    else if (n < 0)
        while (n++) --p;
}

template<typename Iter>
void advance(Iter p, int n) {
    advance_helper(p, n, typename std::iterator_traits<Iter>::iterator_category{});
}

// Example 4
void example4() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin();
    advance(it, 2);
    std::cout << "Advanced vector iterator points to: " << *it << std::endl;
}

// Example 5
void example5() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it1 = v.begin();
    auto it2 = v.begin();

    ++it1; // Pre - increment
    it2++; // Post - increment
    std::cout << "Pre - increment: " << *it1 << ", Post - increment: " << *it2 << std::endl;

    it1 += 2; // Valid for random - access iterator
    std::cout << "Advanced by 2: " << *it1 << std::endl;
}

// Example 6
void example6() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto ri = std::find(v.rbegin(), v.rend(), 3);
    if (ri!= v.rend()) {
        std::cout << "Last occurrence of 3 found at position " << std::distance(v.rbegin(), ri) << " from the end" << std::endl;
    }

    std::vector<int> v2;
    std::fill_n(std::back_inserter(v2), 5, 7);
    for (int i : v2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::vector<int> v3 = {1, 2, 3, 4, 5};
    std::vector<int> v4;
    std::copy(std::make_move_iterator(v3.begin()), std::make_move_iterator(v3.end()), std::back_inserter(v4));
    for (int i : v4) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template<typename Cont>
void print(Cont& c) {
    for (auto p = std::begin(c); p!= std::end(c); ++p)
        std::cout << *p << '\n';
}

// Example 7
void example7() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    print(v);

    int a[] = {1, 2, 3, 4, 5};
    print(a);
}


int main() {
    std::cout << "Example 1:" << std::endl;
    example1();
    std::cout << "Example 2:" << std::endl;
    example2();
    std::cout << "Example 3:" << std::endl;
    example3();
    std::cout << "Example 4:" << std::endl;
    example4();
    std::cout << "Example 5:" << std::endl;
    example5();
    std::cout << "Example 6:" << std::endl;
    example6();
    std::cout << "Example 7:" << std::endl;
    example7();
    return 0;
}