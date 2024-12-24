#include <iostream>
#include <sstream>
#include <iomanip>

using std::ostream;

class Form;
struct Bound_form {
    const Form& f;
    double val;
};
class Form {
    friend ostream& operator<<(ostream&, const Bound_form&);
    int prc;
    int wdt;
    std::ios_base::fmtflags fmt;
public:
    explicit Form(
        int p = 6, std::ios_base::fmtflags f = std::ios_base::fmtflags(0), 
        int w = 0) : prc{p}, fmt{f}, wdt{w} {}
    Bound_form operator()(double d) const {
        return Bound_form{*this, d};
    }
    Form& scientific() { fmt = std::ios_base::scientific; return *this; }
    Form& fixed() { fmt = std::ios_base::fixed; return *this; }
    Form& general() { fmt = std::ios_base::fmtflags(0); return *this; }
    Form& precision(int p) { prc = p; return *this; }
    Form& width(int w) { wdt = w; return *this; }
};
ostream& operator<<(ostream& os, const Bound_form& bf) {
    std::ostringstream s;
    s.precision(bf.f.prc);
    s.setf(bf.f.fmt, std::ios_base::floatfield);
    s << bf.val;
    return os << s.str();
}
void f(double d) {
    Form gen4{4};
    Form sci8;
    sci8.scientific().precision(8);
    std::cout << d << ' ' << gen4(d) << ' ' << sci8(d) << ' ' << d << '\n';
    Form sci{10, std::ios_base::scientific};
    std::cout << d << ' ' << gen4(d) << ' ' << sci(d) << ' ' << d << '\n';
}
int main() {
    f(1234.56789);
    return 0;
}