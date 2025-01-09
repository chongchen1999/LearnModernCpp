// File: messages_facet.cpp

#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Message Data Structures
struct Set {
    vector<string> msgs;
};

struct Cat {
    vector<Set> sets;
};

// Custom Messages Facet
class My_messages : public std::messages<char> {
    vector<Cat>& catalogs;

public:
    explicit My_messages(size_t = 0) : catalogs(*new vector<Cat>) {}
    ~My_messages() { delete &catalogs; }

protected:
    catalog do_open(const string& s, const locale& loc) const override {
        string nn = s + locale().name();
        ifstream f(nn.c_str());
        if (!f) return -1;

        catalogs.push_back(Cat{});
        Cat& c = catalogs.back();

        for (string line; f >> line && line == "<<<";) {
            c.sets.push_back(Set{});
            Set& ss = c.sets.back();

            while (getline(f, line) && line != ">>>") {
                ss.msgs.push_back(line);
            }
        }

        return catalogs.size() - 1;
    }

    string_type do_get(catalog cat, int set, int id, const string_type& def) const override {
        if (catalogs.size() <= cat) return def;
        Cat& c = catalogs[cat];
        if (c.sets.size() <= set) return def;
        Set& s = c.sets[set];
        if (s.msgs.size() <= id) return def;

        return s.msgs[id];
    }

    void do_close(catalog cat) const override {
        if (catalogs.size() > cat) {
            catalogs.erase(catalogs.begin() + cat);
        }
    }
};

// Test Program
int main() {
    if (!std::has_facet<My_messages>(std::locale())) {
        cerr << "No messages facet found in " << locale().name() << '\n';
        return 1;
    }

    const My_messages& m = use_facet<My_messages>(locale());
    string message_directory = "catalog"; // Path to the message catalog
    auto cat = m.open(message_directory, locale());

    if (cat < 0) {
        cerr << "No catalog found\n";
        return 1;
    }

    cout << m.get(cat, 0, 0, "Missed again!") << endl;
    cout << m.get(cat, 1, 2, "Missed again!") << endl;
    cout << m.get(cat, 1, 3, "Missed again!") << endl;
    cout << m.get(cat, 3, 0, "Missed again!") << endl;

    return 0;
}
