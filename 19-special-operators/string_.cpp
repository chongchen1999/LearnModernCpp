#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>

using namespace std;

class String {
public:
    String();
    explicit String(const char* p);
    String(const String& x);
    String& operator=(const String& x);
    String(String&& x) noexcept;
    String& operator=(String&& x) noexcept;
    ~String() { if (short_max < sz) delete[] ptr; }

    char& operator[](int n) { return ptr[n]; }
    char operator[](int n) const { return ptr[n]; }
    char& at(int n) { check(n); return ptr[n]; }
    char at(int n) const { check(n); return ptr[n]; }
    String& operator+=(char c);

    const char* c_str() const { return ptr; }
    int size() const { return sz; }
    int capacity() const { return (sz <= short_max) ? short_max : sz + space; }

private:
    static const int short_max = 15;
    int sz = 0;
    char* ptr = nullptr;
    union {
        int space = 0;
        char ch[short_max + 1];
    };

    void check(int n) const {
        if (n < 0 || sz <= n)
            throw out_of_range("String::at()");
    }

    void copy_from(const String& x);
    void move_from(String& x) noexcept;
};

char* expand(const char* ptr, int n) {
    char* p = new char[n];
    strcpy(p, ptr);
    return p;
}

String::String() : sz{0}, ptr{ch} {
    ch[0] = 0;
}

String::String(const char* p)
    : sz{static_cast<int>(strlen(p))}, ptr{(sz <= short_max) ? ch : new char[sz + 1]}, space{0} {
    strcpy(ptr, p);
}

String::String(const String& x) {
    copy_from(x);
}

String& String::operator=(const String& x) {
    if (this == &x) return *this; // Self-assignment check
    char* p = (short_max < sz) ? ptr : nullptr;
    copy_from(x);
    delete[] p; // Cleanup old memory
    return *this;
}

String::String(String&& x) noexcept {
    move_from(x);
}

String& String::operator=(String&& x) noexcept {
    if (this == &x) return *this; // Self-assignment check
    if (short_max < sz) delete[] ptr; // Cleanup old memory
    move_from(x);
    return *this;
}

void String::copy_from(const String& x) {
    if (x.sz <= short_max) {
        memcpy(this, &x, sizeof(x));
        ptr = ch;
    } else {
        ptr = expand(x.ptr, x.sz + 1);
        sz = x.sz;
        space = 0;
    }
}

void String::move_from(String& x) noexcept {
    if (x.sz <= short_max) {
        memcpy(this, &x, sizeof(x));
        ptr = ch;
    } else {
        ptr = x.ptr;
        sz = x.sz;
        space = x.space;
        x.ptr = x.ch;
        x.sz = 0;
        x.ch[0] = 0;
    }
}

String& String::operator+=(char c) {
    if (sz == short_max) {
        int n = sz + sz + 2;
        char* new_ptr = expand(ptr, n); // Allocate new memory
        if (ptr != ch) delete[] ptr;   // Cleanup if using dynamic memory
        ptr = new_ptr;
        space = n - sz - 2;
    } else if (short_max < sz) {
        if (space == 0) {
            int n = sz + sz + 2;
            char* new_ptr = expand(ptr, n); // Allocate new memory
            delete[] ptr;                  // Cleanup
            ptr = new_ptr;
            space = n - sz - 2;
        } else {
            --space;
        }
    }
    ptr[sz++] = c;
    ptr[sz] = '\0';
    return *this;
}

ostream& operator<<(ostream& os, const String& s) {
    return os << s.c_str();
}

istream& operator>>(istream& is, String& s) {
    s = {};
    is >> ws; // Skip whitespace
    char ch = ' ';
    while (is.get(ch) && !isspace(ch))
        s += ch;
    return is;
}

bool operator==(const String& a, const String& b) {
    if (a.size() != b.size())
        return false;
    for (int i = 0; i != a.size(); ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

bool operator!=(const String& a, const String& b) {
    return !(a == b);
}

char* begin(String& x) {
    return const_cast<char*>(x.c_str());
}

char* end(String& x) {
    return const_cast<char*>(x.c_str() + x.size());
}

const char* begin(const String& x) {
    return x.c_str();
}

const char* end(const String& x) {
    return x.c_str() + x.size();
}

String& operator+=(String& a, const String& b) {
    for (auto x : b)
        a += x;
    return a;
}

String operator+(const String& a, const String& b) {
    String res{a};
    res += b;
    return res;
}

String operator"" _s(const char* p, size_t) {
    return String{p};
}

int main() {
    String s("abcdefghij");
    cout << s << '\n';
    s += 'k';
    s += 'l';
    s += 'm';
    s += 'n';
    cout << s << '\n';

    String s2 = String{"Hell"};
    s2 += String{" and high water"};
    cout << s2 << '\n';

    String s3 = String{"qwerty"};
    s3 = s3;
    String s4 = String{"the quick brown fox jumped over the lazy dog"};
    s4 = s4;
    cout << s3 << " " << s4 << "\n";
    cout << s + String{". "} + s3 + String(". ") + String{"Horsefeathers\n"};

    String buf;
    while (cin >> buf && buf != String{"quit"})
        cout << buf << " " << buf.size() << " " << buf.capacity() << '\n';

    return 0;
}
