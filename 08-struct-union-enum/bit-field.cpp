#include <iostream>
struct PPN {
    unsigned int PFN : 15;
    int : 3;
    unsigned int CCA : 3;
    bool nonreachable : 1;
    bool dirty : 1;
    bool valid : 1;
    bool global : 1;
};

int main() {
    std::cout << "Size of PPN: " << sizeof(PPN) << " bytes\n";
    return 0;
}
