#include <iostream>
#include <string>
#include <tuple>

template<typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void>
struct Tuple : Tuple<T2, T3, T4> {
    T1 x;
    using Base = Tuple<T2, T3, T4>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
        : Base(t2, t3, t4), x(t1) {}
};

template<> struct Tuple<> { Tuple() {} };
template<typename T1> struct Tuple<T1> : Tuple<> {
    T1 x; using Base = Tuple<>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1) : Base(), x(t1) {}
};
template<typename T1, typename T2> struct Tuple<T1, T2> : Tuple<T2> {
    T1 x; using Base = Tuple<T2>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2) : Base(t2), x(t1) {}
};
template<typename T1, typename T2, typename T3> struct Tuple<T1, T2, T3> : Tuple<T2, T3> {
    T1 x; using Base = Tuple<T2, T3>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2, const T3& t3) : Base(t2, t3), x(t1) {}
};

template<typename T1, typename T2, typename T3, typename T4>
void print_elements(std::ostream& os, const Tuple<T1, T2, T3, T4>& t) {
    os << t.x << ", "; print_elements(os, *t.base());
}
template<typename T1, typename T2, typename T3>
void print_elements(std::ostream& os, const Tuple<T1, T2, T3>& t) {
    os << t.x << ", "; print_elements(os, *t.base());
}
template<typename T1, typename T2>
void print_elements(std::ostream& os, const Tuple<T1, T2>& t) {
    os << t.x << ", "; print_elements(os, *t.base());
}
template<typename T1>
void print_elements(std::ostream& os, const Tuple<T1>& t) { os << t.x; }
template<> void print_elements(std::ostream& os, const Tuple<>&) { os << " "; }
template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream& os, const Tuple<T1, T2, T3, T4>& t) {
    os << "{ "; print_elements(os, t); os << " }"; return os;
}

template<typename Ret, int N>
struct getNth {
    template<typename T>
    static Ret& get(T& t) { return getNth<Ret, N - 1>::get(*t.base()); }
};
template<typename Ret>
struct getNth<Ret, 0> {
    template<typename T>
    static Ret& get(T& t) { return t.x; }
};

template<int N, typename T1, typename T2, typename T3, typename T4>
auto& get(Tuple<T1, T2, T3, T4>& t) {
    return getNth<typename std::tuple_element<N, std::tuple<T1, T2, T3, T4>>::type, N>::get(t);
}

template<int N, typename T1, typename T2, typename T3, typename T4>
const auto& get(const Tuple<T1, T2, T3, T4>& t) {
    return getNth<typename std::tuple_element<N, std::tuple<T1, T2, T3, T4>>::type, N>::get(t);
}

template<typename T1, typename T2, typename T3, typename T4>
Tuple<T1, T2, T3, T4> make_tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4) {
    return Tuple<T1, T2, T3, T4>(t1, t2, t3, t4);
}

int main() {
    auto t = make_tuple(1, 2.0, "three", std::string("four"));
    std::cout << t << "\n";
    std::cout << "First element: " << get<0>(t) << "\n";
    std::cout << "Second element: " << get<1>(t) << "\n";
    return 0;
}
