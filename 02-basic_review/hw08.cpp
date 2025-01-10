#include <iostream>
#include <map>

int main() {
    std::map<int, int> m;
    m[0] = m.size();
    std::cout << m[0] << std::endl;
    return 0;
}
