#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <cctype>

using namespace std;

// Define a simple Record type
struct Record {
    string name;
    int val;
};

// Custom hash and equality functions for Record
struct Nocase_hash {
    size_t operator()(const Record& r) const {
        size_t h = 0;
        for (auto x : r.name) {
            h <<= 1;
            h ^= toupper(x);
        }
        return h;
    }
};

struct Nocase_equal {
    bool operator()(const Record& r1, const Record& r2) const {
        if (r1.name.size() != r2.name.size()) return false;
        for (size_t i = 0; i < r1.name.size(); ++i) {
            if (toupper(r1.name[i]) != toupper(r2.name[i])) return false;
        }
        return true;
    }
};

// Custom hash function using standard library hash
size_t hf(const Record& r) {
    return hash<string>()(r.name) ^ hash<int>()(r.val);
}

// Custom equality function
bool eq(const Record& r1, const Record& r2) {
    return r1.name == r2.name && r1.val == r2.val;
}

int main() {
    // Example of vector
    vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);
    cout << "Vector elements: ";
    for (int v : vec) cout << v << " ";
    cout << endl;

    // Example of list
    list<int> lst = {1, 2, 3, 4, 5};
    lst.push_front(0);
    cout << "List elements: ";
    for (int l : lst) cout << l << " ";
    cout << endl;

    // Example of forward_list
    forward_list<int> flst = {1, 2, 3, 4, 5};
    flst.push_front(0);
    cout << "Forward List elements: ";
    for (int f : flst) cout << f << " ";
    cout << endl;

    // Example of map
    map<string, int> score1 = {
        {"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}
    };
    cout << "Map elements: ";
    for (const auto& s : score1) cout << "{" << s.first << "," << s.second << "} ";
    cout << endl;

    // Example of unordered_map
    unordered_map<string, int> score2 = {
        {"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}
    };
    cout << "Unordered Map elements: ";
    for (const auto& s : score2) cout << "{" << s.first << "," << s.second << "} ";
    cout << endl;

    // Example of unordered_set with custom hash and equality
    unordered_set<Record, Nocase_hash, Nocase_equal> records = {
        {"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}
    };
    cout << "Unordered Set elements: ";
    for (const auto& r : records) cout << "{" << r.name << "," << r.val << "} ";
    cout << endl;

    // Example of using custom hash and equality functions
    unordered_set<Record, decltype(&hf), decltype(&eq)> custom_records(10, hf, eq);
    custom_records.insert({"andy", 7});
    custom_records.insert({"al", 9});
    custom_records.insert({"bill", -3});
    custom_records.insert({"barbara", 12});
    cout << "Custom Unordered Set elements: ";
    for (const auto& r : custom_records) cout << "{" << r.name << "," << r.val << "} ";
    cout << endl;

    return 0;
}