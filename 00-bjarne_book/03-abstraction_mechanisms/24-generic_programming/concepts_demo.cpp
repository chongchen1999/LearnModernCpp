#include <iostream>
#include <type_traits>
#include <string>
#include <cstring>

using namespace std;

namespace Estd {

// Concept definitions

template<typename T>
constexpr bool Equality_comparable() {
    return is_same_v<decltype(declval<T>() == declval<T>()), bool> &&
           is_same_v<decltype(declval<T>() != declval<T>()), bool>;
}

template<typename T>
constexpr bool Semiregular() {
    return is_destructible_v<T> &&
           is_default_constructible_v<T> &&
           is_copy_constructible_v<T> &&
           is_copy_assignable_v<T>;
}

template<typename T>
constexpr bool Regular() {
    return Semiregular<T>() && Equality_comparable<T>();
}

template<typename T>
constexpr bool Totally_ordered() {
    return Equality_comparable<T>() &&
           is_same_v<decltype(declval<T>() < declval<T>()), bool> &&
           is_same_v<decltype(declval<T>() > declval<T>()), bool> &&
           is_same_v<decltype(declval<T>() <= declval<T>()), bool> &&
           is_same_v<decltype(declval<T>() >= declval<T>()), bool>;
}

template<typename T>
constexpr bool Ordered() {
    return Regular<T>() && Totally_ordered<T>();
}

template<typename T>
constexpr bool Streamable() {
    return is_same_v<decltype(declval<ostream&>() << declval<T>()), ostream&>;
}

} // namespace Estd

// Example template using concepts

template<typename C>
class String {
    static_assert(Estd::Ordered<C>(), "String's character type is not ordered");

    C* data_;
    size_t length_;

public:
    // Constructors
    String() : data_(nullptr), length_(0) {}
    explicit String(const C* str) {
        length_ = strlen(str);
        data_ = new C[length_ + 1];
        strcpy(data_, str);
    }

    // Copy constructor
    String(const String& other) {
        length_ = other.length_;
        data_ = new C[length_ + 1];
        strcpy(data_, other.data_);
    }

    // Move constructor
    String(String&& other) noexcept : data_(other.data_), length_(other.length_) {
        other.data_ = nullptr;
        other.length_ = 0;
    }

    // Destructor
    ~String() {
        delete[] data_;
    }

    // Copy assignment
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data_;
            length_ = other.length_;
            data_ = new C[length_ + 1];
            strcpy(data_, other.data_);
        }
        return *this;
    }

    // Move assignment
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            length_ = other.length_;
            other.data_ = nullptr;
            other.length_ = 0;
        }
        return *this;
    }

    // Member functions
    size_t size() const { return length_; }

    C operator[](int index) const { 
        if (index >= 0 && static_cast<size_t>(index) < length_) 
            return data_[index]; 
        return C(); 
    }
};

// Overloaded operator<<
template<typename C>
ostream& operator<<(ostream& out, String<C>& s) {
    static_assert(Estd::Streamable<C>(), "String's character not streamable");
    out << '"';
    for (size_t i = 0; i < s.size(); ++i) out << s[i];
    out << '"';
    return out;
}

// Global static assertions
static_assert(Estd::Ordered<char>, "char is not Ordered");
static_assert(Estd::Ordered<std::string>, "std::string is not Ordered");
// static_assert(Estd::Ordered<String<char>>, "String<char> is not Ordered");

int main() {
    String<char> s("Hello");
    cout << s << endl;
    return 0;
}
