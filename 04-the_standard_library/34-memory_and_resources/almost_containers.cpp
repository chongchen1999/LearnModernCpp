#include <array>
#include <bitset>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <algorithm>

int main() {
    // array examples
    std::array<int, 3> a1 = {1, 2, 3};
    std::array<std::string, 4> aa = {"Churchill", "Clare"};
    std::array<int, 0> a0;
    std::array<int, 8> aa2;
    aa2.fill(99);
    for (int i : aa2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::array<int, 10> a;
    auto p = std::find(a.begin(), a.end(), 777);
    std::array<int, 7> a3 = {1, 2, 3, 5, 8, 13, 25};
    auto x1 = std::get<5>(a3);
    auto x2 = a3[5];
    auto sz = std::tuple_size<decltype(a3)>::value;
    std::cout << "x1: " << x1 << ", x2: " << x2 << ", sz: " << sz << std::endl;

    // bitset examples
    std::bitset<10> b1;
    std::bitset<16> b2 = 0xaaaa;
    std::bitset<32> b3 = 0xaaaa;
    std::bitset<10> b4{"1010101010"};
    std::bitset<10> b5{"10110111011110", 4};
    std::bitset<10> b6{std::string{"1010101010"}};
    std::bitset<10> b7{std::string{"10110111011110"}, 4};
    std::bitset<10> b8{std::string{"10110111011110"}, 2, 8};
    std::bitset<9> bs("110001111");
    std::cout << bs << '\n';
    auto bs2 = bs << 3;
    std::cout << bs2 << '\n';
    int i = 123;
    std::bitset<8 * sizeof(int)> b = i;
    std::cout << b.to_string<char, std::char_traits<char>, std::allocator<char>>() << '\n';
    std::cout << b.to_string<char>() << '\n';
    std::cout << b.to_string() << '\n';

    // vector<bool> example
    std::vector<bool> vb(10);
    vb[3] = true;

    // pair examples
    std::pair<std::string, int> pair_{std::string{"Cambridge"}, 1209};
    std::cout << pair_.first << std::endl;
    pair_.second += 800;
    auto p2 = std::make_pair("Harvard", 1736);

    // tuple examples
    auto t = std::make_tuple(2.71828, 299792458, "Hannibal");
    double c;
    std::string name;
    std::tie(c, std::ignore, name) = t;
    std::cout << "c: " << c << ", name: " << name << std::endl;
    std::tuple<std::string, std::vector<double>, int> t2 = 
        std::make_tuple(std::string{"Hello, tuples!"}, std::vector<double>{1, 2, 3}, int{'x'});

    return 0;
}
