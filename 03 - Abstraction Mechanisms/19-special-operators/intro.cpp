#include <iostream>
#include <cstring>

// Subscripting Example
class SubscriptExample {
private:
    int arr[5];
public:
    SubscriptExample() { for (int i = 0; i < 5; ++i) arr[i] = i * 10; }
    int operator[](int index) const { return arr[index]; }
};

// Function Call Example
class FunctionCallExample {
public:
    int operator()(int a, int b) { return a + b; }
};

// Dereference Example
class DereferenceExample {
private:
    int value;
public:
    DereferenceExample(int val) : value(val) {}
    int& operator*() { return value; }
};

// Increment Example
class IncrementExample {
private:
    int val;
public:
    IncrementExample(int v) : val(v) {}
    IncrementExample& operator++() { ++val; return *this; } // Prefix
    IncrementExample operator++(int) { IncrementExample temp = *this; ++val; return temp; } // Postfix
    void print() { std::cout << "Value: " << val << '\n'; }
};

// Allocation Example
class AllocationExample {
public:
    void* operator new(size_t size) {
        std::cout << "Custom new called\n";
        return ::operator new(size);
    }
    void operator delete(void* ptr) {
        std::cout << "Custom delete called\n";
        ::operator delete(ptr);
    }
};

// String Class
class String {
private:
    char* str;
    size_t size;
public:
    String(const char* s = "") : size(strlen(s)) {
        str = new char[size + 1];
        strcpy(str, s);
    }
    String(const String& other) {
        size = other.size;
        str = new char[size + 1];
        strcpy(str, other.str);
    }
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            size = other.size;
            str = new char[size + 1];
            strcpy(str, other.str);
        }
        return *this;
    }
    char& operator[](int index) { return str[index]; }
    ~String() { delete[] str; }
    void print() const { std::cout << str << '\n'; }
};

// Friend Example
class FriendExample {
private:
    int value;
public:
    FriendExample(int val) : value(val) {}
    friend void showValue(const FriendExample& obj);
};
void showValue(const FriendExample& obj) {
    std::cout << "Value: " << obj.value << '\n';
}

int main() {
    // Subscripting Example
    SubscriptExample sub;
    std::cout << "Subscript Example: " << sub[2] << "\n";

    // Function Call Example
    FunctionCallExample func;
    std::cout << "Function Call Example: " << func(3, 4) << "\n";

    // Dereference Example
    DereferenceExample deref(42);
    std::cout << "Dereference Example: " << *deref << "\n";

    // Increment Example
    IncrementExample inc(10);
    ++inc;
    inc++;
    inc.print();

    // Allocation Example
    AllocationExample* alloc = new AllocationExample();
    delete alloc;

    // String Example
    String s1("Hello");
    s1.print();
    String s2 = s1;
    s2[0] = 'h';
    s2.print();

    // Friend Example
    FriendExample fr(77);
    showValue(fr);

    return 0;
}
