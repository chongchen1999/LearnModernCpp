#include <iostream>
#include <regex>
#include <string>
#include <fstream>

// Function to check if a string is an identifier
bool is_identifier(const std::string& s) {
    std::regex pat {"[_[:alpha:]]\\w*"};
    return std::regex_match(s, pat);
}

// Function to search for misspellings of a name
void search_misspellings() {
    std::regex pat {"[Ss]tro?u?v?p?stra?o?u?p?b?"};
    std::smatch m;
    for (std::string s; std::cin >> s; )
        if (std::regex_search(s, m, pat))
            if (m[0]!= "stroustrup" && m[0]!= "Stroustrup")
                std::cout << "Found: " << m[0] << '\n';
}

// Function to replace word - number pairs in a string
void replace_word_number_pairs() {
    std::string input {"x 1 y2 22 zaq 34567"};
    std::regex pat {"(\\w+)\\s(\\d+)"};
    std::string format {"{$1,$2}\n"};
    std::cout << std::regex_replace(input, pat, format);
}

// Function to output whitespace - separated words in a string
void output_whitespace_separated_words() {
    std::string input = "aa as; asd ++eˆasdf asdfg";
    std::regex pat {R"(\\s+(\\w+))"};
    for (std::sregex_iterator p(input.begin(), input.end(), pat); p!= std::sregex_iterator{}; ++p)
        std::cout << (*p)[1] << '\n';
}

// Function to iterate over specific sub - matches
void iterate_over_submatches() {
    std::string input {"aa::bb cc::dd ee::ff"};
    std::regex pat {R"((\\w+)([[:punct:]]+)(\\w+)\\s*)"};
    std::sregex_token_iterator end {};
    for (std::sregex_token_iterator p{input.begin(), input.end(), pat, {1, 3}}; p!= end; ++p)
        std::cout << *p << '\n';
}

int main() {
    // Test is_identifier
    std::cout << "Testing is_identifier:\n";
    std::cout << std::boolalpha << is_identifier("test123") << '\n';
    std::cout << std::boolalpha << is_identifier("123test") << '\n';

    // Test search_misspellings
    std::cout << "\nTesting search_misspellings:\n";
    // Manually input some test strings here in the console
    search_misspellings();

    // Test replace_word_number_pairs
    std::cout << "\nTesting replace_word_number_pairs:\n";
    replace_word_number_pairs();

    // Test output_whitespace_separated_words
    std::cout << "\nTesting output_whitespace_separated_words:\n";
    output_whitespace_separated_words();

    // Test iterate_over_submatches
    std::cout << "\nTesting iterate_over_submatches:\n";
    iterate_over_submatches();

    return 0;
}