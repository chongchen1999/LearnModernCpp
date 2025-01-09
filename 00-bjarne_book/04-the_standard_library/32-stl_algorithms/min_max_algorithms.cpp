#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

int main() {
    // Example 1: Finding the minimum and maximum of two values
    int x = 7;
    int y = 9;
    int smaller = min(x, y);
    int larger = max(x, y);
    cout << "min(x, y) = " << smaller << '\n';
    cout << "max(x, y) = " << larger << '\n';

    // Example 2: Finding the minimum and maximum in a sequence
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    auto min_it = min_element(v.begin(), v.end());
    auto max_it = max_element(v.begin(), v.end());
    cout << "min_element(v) = " << *min_it << '\n';
    cout << "max_element(v) = " << *max_it << '\n';

    // Example 3: Finding the minimum and maximum in a sequence with a custom comparator
    string s = "Large_Hadron_Collider";
    auto p = minmax_element(s.begin(), s.end(), [](char c1, char c2) {
        return toupper(c1) < toupper(c2);
    });
    cout << "min==" << *(p.first) << ' ' << "max==" << *(p.second) << '\n';

    return 0;
}