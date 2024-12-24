#include <locale>
#include <codecvt>
#include <string>
#include <iostream>
#include <algorithm>

// Count spaces using ctype facet
int count_spaces(const std::string& s, const std::locale& loc) {
    const std::ctype<char>& ct = std::use_facet<std::ctype<char>>(loc);
    int count = 0;
    for (char c : s) {
        if (ct.is(std::ctype_base::space, c)) {
            ++count;
        }
    }
    return count;
}

// Custom codecvt facet to convert characters to uppercase
class Cvt_to_upper : public std::codecvt<char, char, std::mbstate_t> {
public:
    explicit Cvt_to_upper(size_t refs = 0) : std::codecvt<char, char, std::mbstate_t>(refs) {}

protected:
    result do_in(
        std::mbstate_t&, const char* from, const char* from_end, 
        const char*& from_next, char* to, char* to_end, char*& to_next
    ) const override {
        for (
            from_next = from, to_next = to; 
            from_next != from_end && to_next != to_end; 
            ++from_next, ++to_next
        ) {
            *to_next = std::toupper(*from_next);
        }
        return ok;
    }

    result do_out(std::mbstate_t& state, const char* from, const char* from_end, const char*& from_next,
                                char* to, char* to_end, char*& to_next) const {
        return do_in(state, from, from_end, from_next, to, to_end, to_next);
    }

    result do_unshift(std::mbstate_t&, char* to, char* to_end, char*& to_next) const override {
        to_next = to;
        return ok;
    }

    int do_encoding() const noexcept override { return 1; }
    bool do_always_noconv() const noexcept override { return false; }
    int do_length(std::mbstate_t&, const char* from, const char* from_end, size_t max) const override {
        return std::min(static_cast<size_t>(from_end - from), max);
    }
    int do_max_length() const noexcept override { return 1; }
};

int main() {
    std::locale ulocale(std::locale(), new Cvt_to_upper);
    std::cin.imbue(ulocale);

    std::string test = "Hello World! 123";
    std::cout << "Spaces in \"" << test << "\": " << count_spaces(test, ulocale) << '\n';

    std::cout << "Enter text to convert to uppercase: ";
    for (char ch; std::cin >> ch;) {
        std::cout << ch;
    }
    return 0;
}
