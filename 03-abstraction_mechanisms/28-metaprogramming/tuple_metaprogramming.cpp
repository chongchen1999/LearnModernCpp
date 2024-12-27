#include <iostream>
#include <string>
using namespace std;

// Nil type definition for empty elements
struct Nil {};

// Primary Tuple Template
template <typename T1 = Nil, typename T2 = Nil, typename T3 = Nil,
          typename T4 = Nil>
struct Tuple : Tuple<T2, T3, T4> {
    T1 x;
    using Base = Tuple<T2, T3, T4>;

    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }

    Tuple(const T1& t1 = T1{}, const T2& t2 = T2{}, const T3& t3 = T3{},
          const T4& t4 = T4{})
        : Base{t2, t3, t4}, x{t1} {}
};

// Specializations
template <>
struct Tuple<> {
    Tuple() {}
};

template <typename T1>
struct Tuple<T1> : Tuple<> {
    T1 x;
    using Base = Tuple<>;

    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }

    Tuple(const T1& t1 = T1{}) : Base{}, x{t1} {}
};

template <typename T1, typename T2>
struct Tuple<T1, T2> : Tuple<T2> {
    T1 x;
    using Base = Tuple<T2>;

    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }

    Tuple(const T1& t1 = T1{}, const T2& t2 = T2{}) : Base{t2}, x{t1} {}
};

template <typename T1, typename T2, typename T3>
struct Tuple<T1, T2, T3> : Tuple<T2, T3> {
    T1 x;
    using Base = Tuple<T2, T3>;

    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }

    Tuple(const T1& t1 = T1{}, const T2& t2 = T2{}, const T3& t3 = T3{})
        : Base{t2, t3}, x{t1} {}
};

// Type Selection Helper
template <int N, typename T1, typename T2, typename T3, typename T4>
struct Select;

template <typename T1, typename T2, typename T3, typename T4>
struct Select<0, T1, T2, T3, T4> {
    using Type = T1;
};

template <typename T1, typename T2, typename T3, typename T4>
struct Select<1, T1, T2, T3, T4> {
    using Type = T2;
};

template <typename T1, typename T2, typename T3, typename T4>
struct Select<2, T1, T2, T3, T4> {
    using Type = T3;
};

template <typename T1, typename T2, typename T3, typename T4>
struct Select<3, T1, T2, T3, T4> {
    using Type = T4;
};

// Output Function
template <typename T1, typename T2, typename T3, typename T4>
void print_elements(ostream& os, const Tuple<T1, T2, T3, T4>& t) {
    os << t.x << ", ";
    print_elements(os, *t.base());
}

template <>
void print_elements(ostream& os, const Tuple<>& t) {
    os << " ";
}

template <typename T1, typename T2, typename T3, typename T4>
ostream& operator<<(ostream& os, const Tuple<T1, T2, T3, T4>& t) {
    os << "{ ";
    print_elements(os, t);
    os << " }";
    return os;
}

// Element Access
template <typename Ret, int N>
struct getNth {
    template <typename T>
    static Ret& get(T& t) {
        return getNth<Ret, N - 1>::get(*t.base());
    }
};

template <typename Ret>
struct getNth<Ret, 0> {
    template <typename T>
    static Ret& get(T& t) {
        return t.x;
    }
};

template <int N, typename T1, typename T2, typename T3, typename T4>
typename Select<N, T1, T2, T3, T4>::Type& get(Tuple<T1, T2, T3, T4>& t) {
    using Ret = typename Select<N, T1, T2, T3, T4>::Type;
    return getNth<Ret, N>::get(t);
}

// Make Tuple
template <typename T1, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
Tuple<T1, T2, T3, T4> make_tuple(const T1& t1, const T2& t2 = T2{},
                                 const T3& t3 = T3{}, const T4& t4 = T4{}) {
    return Tuple<T1, T2, T3, T4>{t1, t2, t3, t4};
}

// Example
int main() {
    auto t = make_tuple(1, std::string{"Hello"}, 3.5, true);
    cout << t << endl;

    cout << "Element 2: " << get<2>(t) << endl;
}