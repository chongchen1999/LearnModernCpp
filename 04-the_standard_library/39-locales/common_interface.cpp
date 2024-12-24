#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <fstream>
#include <sstream>

// Character Classification Example
template<class C>
inline bool is_space(C c, const std::locale& loc) {
    return std::use_facet<std::ctype<C>>(loc).is(std::ctype_base::space, c);
}

// Character Conversion Example
template<class C>
inline C to_upper(C c, const std::locale& loc) {
    return std::use_facet<std::ctype<C>>(loc).toupper(c);
}

// String Conversion Example
void test_string_conversion() {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string s8 = reinterpret_cast<const char*>(u8"This is a UTF−8 string");
    std::wstring s16 = converter.from_bytes(s8);
    std::string s88 = converter.to_bytes(s16);
    if (s8 != s88) {
        std::cerr << "Insane!\n";
    }
}

// Buffer Conversion Example
void buffer_conversion_example() {
    std::wifstream input("example.txt");
    input.imbue(std::locale(input.getloc(), new std::codecvt_utf8<wchar_t>));
    std::wostringstream oss;
    oss << input.rdbuf();
    std::wcout << L"Content: " << oss.str() << L"\n";
}

// Main Function
int main() {
    // Character Classification
    char c = ' ';
    std::locale loc;
    if (is_space(c, loc)) {
        std::cout << "Character is a space\n";
    }

    // Character Conversion
    char c2 = 'a';
    std::cout << "Uppercase: " << to_upper(c2, loc) << "\n";

    // String Conversion
    test_string_conversion();

    // Buffer Conversion
    buffer_conversion_example();

    return 0;
}
