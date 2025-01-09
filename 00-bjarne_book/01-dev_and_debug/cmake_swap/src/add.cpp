#include "add.h"

template <typename T>
T add(const T &a, const T &b) {
    return a + b;
}

template int add(const int &, const int &);