#include <iostream>
#include <map>
#include <string>
#include <vector>

class Std_interface {
public:
    virtual void start() = 0;
    virtual void suspend() = 0;
    virtual void resume() = 0;
    virtual void quit() = 0;
    virtual void full_size() = 0;
    virtual void small() = 0;
    virtual ~Std_interface() {}
};

using Pstd_mem = void (Std_interface::*)();

void f(Std_interface* p) {
    Pstd_mem s = &Std_interface::suspend;
    p->suspend();
    (p->*s)();
}

void call_member(std::string var, std::string oper) {
    std::map<std::string, Std_interface*> variable;
    std::map<std::string, Pstd_mem> operation;
    // Assuming variable and operation are initialized with valid data:
    (variable[var]->*operation[oper])();
}

struct C {
    static void print2(int x) { std::cout << "C" << x << '\n'; }
    const char* val;
    int i;
    static const int j;
    void print(int x) { std::cout << val << x << '\n'; }
    C(const char* v) : val(v), i(0) {}
};
const int C::j = 23;

using Pmfi = void (C::*)(int);
using Pm = const char* C::*;

void demo(C& z1, C& z2) {
    C* p = &z2;
    Pmfi pf = &C::print;
    Pm pm = &C::val;

    z1.print(1);
    (z1.*pf)(2);
    z1.*pm = "nv1 ";
    p->*pm = "nv2 ";
    z2.print(3);
    (p->*pf)(4);

    // std::cout << sizeof(pf) << '\n';
    // std::cout << reinterpret_cast<void*>(pf) << '\n';
    // std::cout << reinterpret_cast<void*>(pm) << '\n';
}

class Text : public Std_interface {
public:
    void start() override {}
    void suspend() override {}
    void resume() override {}
    void quit() override {}
    void full_size() override {}
    void small() override {}
    virtual void print() {}

private:
    std::vector<int> s;
};

void demoContravariance() {
    // void (Std_interface::*pmi)() = &Text::print; // Error
    void (Text::*pmt)() = &Std_interface::start; // OK
}

int g() { return 233; }

void demo_p2f() {
    using ptr2f = int (*)();
    ptr2f p = &g;
    // std::cout << reinterpret_cast<void*>(p) << '\n';
}

int main() {
    // Example usage of pointers to members
    C z1("z1"), z2("z2");
    demo(z1, z2);

    // using ptr2f = int (*)();
    // ptr2f p = &f;
    auto p = &g;
    // std::cout << reinterpret_cast<void*>(p) << '\n';

    auto p2 = &C::print;
    auto p3 = &C::val;
    auto p4 = &C::print2;
    auto p5 = &C::j;
    // std::cout << reinterpret_cast<void*>(p2) << '\n';
    std::cout << "sizeof p2" << ' ' << sizeof(p2) << '\n';
    std::cout << "sizeof p3" << ' ' << sizeof(p3) << '\n';
    std::cout << "sizeof p4" << ' ' << sizeof(p4) << '\n';
    std::cout << "sizeof p5" << ' ' << sizeof(p5) << '\n';
    std::cout << sizeof(void*) << '\n';

    demo_p2f();

    return 0;
}
