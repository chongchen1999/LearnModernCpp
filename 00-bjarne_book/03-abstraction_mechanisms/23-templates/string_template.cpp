#include <cstring>
#include <iostream>
#include <map>

template <typename T>
class String {
   public:
    T* data;
    size_t size;

    String(const T* str) {
        size = strlen(str);
        data = new T[size + 1];
        strcpy(data, str);
    }

    ~String() { delete[] data; }

    bool operator<(const String& other) const {
        return strcmp(data, other.data) < 0;
    }

    String(String&& other) noexcept {
        data = other.data;
        size = other.size;
        other.data = nullptr;
    }

    String(const String& other) {
        size = other.size;
        data = new T[size + 1];
        strcpy(data, other.data);
    }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.data;
        return os;
    }
};

int main() {
    std::map<String<char>, int> myMap;

    myMap[String<char>("apple")] = 1;
    myMap[String<char>("banana")] = 2;

    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << '\n';
    }

    return 0;
}
