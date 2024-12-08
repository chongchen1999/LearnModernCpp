#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace Parser {
    double expr(bool);  // Declaration
    double term(bool);
    double prim(bool);
}

double Parser::expr(bool b) {
    return b ? 1.0 : 0.0;
}

double Parser::term(bool b) {
    return b ? 2.0 : 0.0;
}

double Parser::prim(bool b) {
    return b ? 3.0 : 0.0;
}

namespace Chrono {
    class Date {
    public:
        std::string to_string() const { return "Date object"; }
    };

    bool operator==(const Date&, const std::string&) {
        return true;
    }

    std::string format(const Date&) {
        return "Formatted Date";
    }
}

void using_declaration_example() {
    using std::string;

    string s = "Hello, world!";
    std::cout << "Using declaration: " << s << "\n";
}

namespace using_directive {

    using namespace std;
    vector<string> split(const string& s) {
        vector<string> res;
        istringstream iss(s);
        for (string buf; iss >> buf;) {
            res.push_back(buf);
        }
        return res;
    }
    void using_directive_example() {
        string s = "Hello world!";
        auto words = split(s);
        for (const auto& word : words) {
            cout << "Word: " << word << "\n";
        }
    }
}

void argument_dependent_lookup_example() {
    Chrono::Date date;
    std::cout << "ADL Example: " << format(date) << "\n";
}

int main() {
    std::cout << "Explicit Qualification:\n";
    std::cout << "Parser::expr(true): " << Parser::expr(true) << "\n";

    std::cout << "\nUsing Declarations:\n";
    using_declaration_example();

    std::cout << "\nUsing Directives:\n";
    using_directive::using_directive_example();

    std::cout << "\nArgument-Dependent Lookup:\n";
    argument_dependent_lookup_example();

    return 0;
}
