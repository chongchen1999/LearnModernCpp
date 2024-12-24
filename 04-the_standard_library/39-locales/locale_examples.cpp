#include <locale>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void compare_strings(const std::string& s1, const std::string& s2, const std::locale& loc) {
    if (loc(s1, s2)) {
        std::cout << s1 << " is less than " << s2 << " according to the locale.\n";
    } else {
        std::cout << s1 << " is not less than " << s2 << " according to the locale.\n";
    }
}

void sort_strings(std::vector<std::string>& v, const std::locale& loc) {
    std::sort(v.begin(), v.end(), loc);
    std::cout << "Sorted strings: ";
    for (const auto& str : v) {
        std::cout << str << " ";
    }
    std::cout << "\n";
}

void set_locale(const char* name) {
    try {
        std::locale loc{name};
        std::cout << "Locale set to: " << loc.name() << "\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to set locale: " << e.what() << "\n";
    }
}

void combine_locales() {
    std::locale loc1{"C"};
    std::locale loc2{"en_US.UTF-8"};
    std::locale combined{loc1, loc2, std::locale::numeric};
    std::cout << "Combined locale: " << combined.name() << "\n";
}

int main() {
    // Comparing strings
    std::locale loc{"en_US.UTF-8"};
    compare_strings("apple", "banana", loc);

    // Sorting strings
    std::vector<std::string> v{"apple", "banana", "cherry"};
    sort_strings(v, loc);

    // Setting locale
    set_locale("fr_FR.UTF-8");

    // Combining locales
    combine_locales();

    return 0;
}
