#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;

// Token types
enum class Kind : char {
    name, number, end,
    plus = '+', minus = '-', mul = '*', div = '/', print = ';', assign = '=', lp = '(', rp = ')'
};

// Token structure
struct Token {
    Kind kind;
    string string_value;
    double number_value;
};

// Token stream class
class Token_stream {
public:
    Token_stream(istream& s) : ip{&s}, owns{false} {}
    Token_stream(istream* p) : ip{p}, owns{true} {}
    ~Token_stream() { close(); }

    Token get();
    const Token& current() { return ct; }
    void set_input(istream& s) { close(); ip = &s; owns = false; }
    void set_input(istream* p) { close(); ip = p; owns = true; }

private:
    void close() { if (owns) delete ip; }
    istream* ip;
    bool owns;
    Token ct {Kind::end};
};

Token Token_stream::get() {
    char ch;
    do { // skip whitespace except '\n'
        if (!ip->get(ch)) return ct = {Kind::end};
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case ';':
        case '\n':
            return ct = {Kind::print};
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return ct = {static_cast<Kind>(ch)};
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        case '.':
            ip->putback(ch);
            *ip >> ct.number_value;
            ct.kind = Kind::number;
            return ct;
        default:
            if (isalpha(ch)) {
                ct.string_value = ch;
                while (ip->get(ch) && isalnum(ch))
                    ct.string_value += ch;
                ip->putback(ch);
                ct.kind = Kind::name;
                return ct;
            }
            error("bad token");
            return ct = {Kind::print};
    }
}

// Symbol table
map<string, double> table;

// Error handling
int no_of_errors;
double error(const string& s) {
    no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}

// Parser functions
double expr(bool get, Token_stream& ts);
double term(bool get, Token_stream& ts);
double prim(bool get, Token_stream& ts);

double expr(bool get, Token_stream& ts) {
    double left = term(get, ts);
    for (;;) {
        switch (ts.current().kind) {
        case Kind::plus:
            left += term(true, ts);
            break;
        case Kind::minus:
            left -= term(true, ts);
            break;
        default:
            return left;
        }
    }
}

double term(bool get, Token_stream& ts) {
    double left = prim(get, ts);
    for (;;) {
        switch (ts.current().kind) {
        case Kind::mul:
            left *= prim(true, ts);
            break;
        case Kind::div:
            if (auto d = prim(true, ts)) {
                left /= d;
                break;
            }
            return error("divide by 0");
        default:
            return left;
        }
    }
}

double prim(bool get, Token_stream& ts) {
    if (get) ts.get();
    switch (ts.current().kind) {
    case Kind::number: {
        double v = ts.current().number_value;
        ts.get();
        return v;
    }
    case Kind::name: {
        double& v = table[ts.current().string_value];
        if (ts.get().kind == Kind::assign) v = expr(true, ts);
        return v;
    }
    case Kind::minus:
        return -prim(true, ts);
    case Kind::lp: {
        auto e = expr(true, ts);
        if (ts.current().kind != Kind::rp) return error("')' expected");
        ts.get();
        return e;
    }
    default:
        return error("primary expected");
    }
}

// Calculate function
void calculate(Token_stream& ts) {
    for (;;) {
        ts.get();
        if (ts.current().kind == Kind::end) break;
        if (ts.current().kind == Kind::print) continue;
        cout << expr(false, ts) << '\n';
    }
}

// Main function
int main(int argc, char* argv[]) {
    Token_stream ts {cin};

    switch (argc) {
    case 1:
        break;
    case 2:
        ts.set_input(new istringstream{argv[1]});
        break;
    default:
        error("too many arguments");
        return 1;
    }

    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    calculate(ts);
    return no_of_errors;
}