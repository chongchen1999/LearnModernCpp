#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <iterator>

template<typename Out, typename T>
class raw_storage_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void> {
    Out p;
public:
    explicit raw_storage_iterator(Out pp) : p{pp} {}
    raw_storage_iterator& operator*() { return *this; }
    raw_storage_iterator& operator=(const T& val) {
        new(&*p) T{val};
        return *this;
    }
    raw_storage_iterator& operator++() { ++p; return *this; }
    raw_storage_iterator operator++(int) {
        auto t = *this;
        ++p;
        return t;
    }
};

void testTemporaryBuffer() {
    auto pp = std::get_temporary_buffer<std::string>(1000);
    if (pp.second < 1000) {
        std::cerr << "Allocation failure" << std::endl;
    } else {
        std::cout << "Allocated space for " << pp.second << " strings" << std::endl;
    }
    std::return_temporary_buffer(pp.first);
}

void testRawStorageIterator() {
    auto pp = std::get_temporary_buffer<std::string>(1000);
    if (pp.second < 1000) {
        std::cerr << "Allocation failure" << std::endl;
        return;
    }
    auto p = raw_storage_iterator<std::string*, std::string>(pp.first);
    char seed[] = "abc";
    std::generate_n(p, 10, [&] {
        std::next_permutation(seed, seed + sizeof(seed) - 1);
        return std::string(seed);
    });
    // Do something with the generated strings
    std::return_temporary_buffer(pp.first);
}

int main() {
    testTemporaryBuffer();
    testRawStorageIterator();
    return 0;
}