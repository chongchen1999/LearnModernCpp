#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <string>
#include <cassert>
#include <cctype>

using namespace std;

void increment_all(vector<int>& v) {
    for_each(v.begin(), v.end(), [](int& x) { ++x; });
}

vector<double> scale(const vector<double>& val, const vector<double>& div) {
    assert(val.size() <= div.size());
    assert(all_of(div.begin(), div.end(), [](double x) { return x > 0; }));
    vector<double> res(val.size());
    for (size_t i = 0; i < val.size(); ++i)
        res[i] = val[i] / div[i];
    return res;
}

void f(const string& s) {
    auto n_space = count(s.begin(), s.end(), ' ');
    auto n_whitespace = count_if(s.begin(), s.end(), [](unsigned char c) { return std::isspace(c); });
}

void f_find(const string& s) {
    auto p_space = find(s.begin(), s.end(), ' ');
    auto p_whitespace = find_if(s.begin(), s.end(), [](unsigned char c) { return std::isspace(c); });
}

void toupper(string& s) {
    transform(s.begin(), s.end(), s.begin(), 
             [](unsigned char c) { return std::toupper(c); });
}

void f_copy(const list<string>& lc, ostream& os) {
    copy(lc.begin(), lc.end(), ostream_iterator<string>(os));
}

void f_unique(list<string>& ls, vector<string>& vs) {
    ls.sort();
    unique_copy(ls.begin(), ls.end(), back_inserter(vs));
}

void f_remove() {
    string s = "*CamelCase*IsUgly*";
    auto p = remove(s.begin(), s.end(), '*');
    s.erase(p, s.end());
    cout << s << '\n';
}

template<typename List>
void sort_list(List& lst) {
    vector<typename List::value_type> v{lst.begin(), lst.end()};
    sort(v.begin(), v.end());
    assert(v.size() == lst.size());
    copy(v.begin(), v.end(), lst.begin());
}

void f_binary_search(const vector<int>& c) {
    if (binary_search(c.begin(), c.end(), 7)) {
        // is 7 in c?
    }
}

void f_merge() {
    vector<int> v{3, 1, 4, 2};
    list<double> lst{0.5, 1.5, 2, 2.5};
    sort(v.begin(), v.end());
    vector<double> v2;
    v2.reserve(v.size() + lst.size());
    merge(v.begin(), v.end(), lst.begin(), lst.end(), back_inserter(v2));
    for (double x : v2)
        cout << x << ", ";
    cout << '\n';
}

void f_set_union() {
    string s1 = "qwertyasdfgzxcvb";
    string s2 = "poiuyasdfg/.,mnb";
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    string s3;
    s3.reserve(s1.size() + s2.size());
    auto up = set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(s3));
    cout << s3 << '\n';
}

void f_heap() {
    string s = "herewego";
    make_heap(s.begin(), s.end());
    pop_heap(s.begin(), s.end());
    pop_heap(s.begin(), s.end() - 1);
    pop_heap(s.begin(), s.end() - 2);
    *(s.end() - 3) = 'f';
    push_heap(s.begin(), s.end() - 2);
    *(s.end() - 2) = 'x';
    push_heap(s.begin(), s.end() - 1);
    *(s.end() - 1) = 'y';
    push_heap(s.begin(), s.end());
    sort_heap(s.begin(), s.end());
    reverse(s.begin(), s.end());
    cout << s << '\n';
}

void f_lexicographical_compare() {
    string n1 = "10000";
    string n2 = "999";
    bool b1 = lexicographical_compare(n1.begin(), n1.end(), n2.begin(), n2.end());
    cout << "b1: " << b1 << '\n';

    n1 = "Zebra";
    n2 = "Aardvark";
    bool b2 = lexicographical_compare(n1.begin(), n1.end(), n2.begin(), n2.end());
    cout << "b2: " << b2 << '\n';
}

int main() {
    vector<int> v = {1, 2, 3, 4};
    increment_all(v);
    for (int x : v) cout << x << ' ';
    cout << '\n';

    vector<double> val = {1.0, 2.0, 3.0};
    vector<double> div = {1.0, 2.0, 3.0, 4.0};
    vector<double> res = scale(val, div);
    for (double x : res) cout << x << ' ';
    cout << '\n';

    f("Hello World");
    f_find("Hello World");

    string s = "hello";
    toupper(s);
    cout << s << '\n';

    list<string> lc = {"Club1", "Club2", "Club3"};
    f_copy(lc, cout);
    cout << '\n';

    list<string> ls = {"a", "b", "a", "c"};
    vector<string> vs;
    f_unique(ls, vs);
    for (const string& str : vs) cout << str << ' ';
    cout << '\n';

    f_remove();

    list<int> lst = {3, 1, 4, 2};
    sort_list(lst);
    for (int x : lst) cout << x << ' ';
    cout << '\n';

    vector<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    f_binary_search(c);

    f_merge();
    f_set_union();
    f_heap();
    f_lexicographical_compare();

    return 0;
}