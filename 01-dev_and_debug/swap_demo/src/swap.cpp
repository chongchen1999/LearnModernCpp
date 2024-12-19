#include "swap.h"
#include <utility>

template <typename T>
void swap(T &a, T &b) {
    T temp = std::move(a);
    a = b;
    b = std::move(temp);
}

template void swap(int &, int &);