#include <iostream>
#include <string>

// Forward declarations
class Nil {};  // Used as default template parameter

template<typename T1=Nil, typename T2=Nil, typename T3=Nil, typename T4=Nil>
struct Tuple;

// Helper type to select the Nth type from a list of types
template<int N, typename T1, typename T2=Nil, typename T3=Nil, typename T4=Nil>
struct Select {
    using type = T1;  // Default case
};

template<typename T1, typename T2, typename T3, typename T4>
struct Select<1, T1, T2, T3, T4> {
    using type = T2;
};

template<typename T1, typename T2, typename T3, typename T4>
struct Select<2, T1, T2, T3, T4> {
    using type = T3;
};

template<typename T1, typename T2, typename T3, typename T4>
struct Select<3, T1, T2, T3, T4> {
    using type = T4;
};

// Tuple specializations
template<>
struct Tuple<> {  // 0-tuple
    Tuple() {}
};

template<typename T1>
struct Tuple<T1> : Tuple<> {  // 1-tuple
    T1 x;
    using Base = Tuple<>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1) :Base{}, x{t1} { }
};

template<typename T1, typename T2>
struct Tuple<T1, T2> : Tuple<T2> {  // 2-tuple
    T1 x;
    using Base = Tuple<T2>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2) :Base{t2}, x{t1} { }
};

template<typename T1, typename T2, typename T3>
struct Tuple<T1, T2, T3> : Tuple<T2, T3> {  // 3-tuple
    T1 x;
    using Base = Tuple<T2, T3>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2, const T3& t3) :Base{t2, t3}, x{t1} { }
};

template<typename T1, typename T2, typename T3, typename T4>
struct Tuple : Tuple<T2, T3, T4> {  // 4-tuple
    T1 x;
    using Base = Tuple<T2, T3, T4>;
    Base* base() { return static_cast<Base*>(this); }
    const Base* base() const { return static_cast<const Base*>(this); }
    Tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4) :Base{t2,t3,t4}, x{t1} { }
};

// Print functions
template<typename T1, typename T2, typename T3, typename T4>
void print_elements(std::ostream& os, const Tuple<T1,T2,T3,T4>& t) {
    os << t.x << ", ";
    print_elements(os,*t.base());
}

template<typename T1, typename T2, typename T3>
void print_elements(std::ostream& os, const Tuple<T1,T2,T3>& t) {
    os << t.x << ", ";
    print_elements(os,*t.base());
}

template<typename T1, typename T2>
void print_elements(std::ostream& os, const Tuple<T1,T2>& t) {
    os << t.x << ", ";
    print_elements(os,*t.base());
}

template<typename T1>
void print_elements(std::ostream& os, const Tuple<T1>& t) {
    os << t.x;
}

template<>
void print_elements(std::ostream& os, const Tuple<>& t) {
    os << " ";
}

// Output operator
template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream& os, const Tuple<T1,T2,T3,T4>& t) {
    os << "{ ";
    print_elements(os,t);
    os << " }";
    return os;
}

// Element access
template<typename Ret, int N>
struct getNth {
    template<typename T>
    static Ret& get(T& t) {
        return getNth<Ret,N-1>::get(*t.base());
    }
    
    template<typename T>
    static const Ret& get(const T& t) {
        return getNth<Ret,N-1>::get(*t.base());
    }
};

template<typename Ret>
struct getNth<Ret,0> {
    template<typename T> 
    static Ret& get(T& t) { return t.x; }
    
    template<typename T> 
    static const Ret& get(const T& t) { return t.x; }
};

// get function templates
template<int N, typename T1, typename T2, typename T3, typename T4>
typename Select<N, T1, T2, T3, T4>::type& 
get(Tuple<T1, T2, T3, T4>& t) {
    return getNth<typename Select<N, T1, T2, T3, T4>::type,N>::get(t);
}

template<int N, typename T1, typename T2, typename T3, typename T4>
const typename Select<N, T1, T2, T3, T4>::type& 
get(const Tuple<T1, T2, T3, T4>& t) {
    return getNth<typename Select<N, T1, T2, T3, T4>::type,N>::get(t);
}

// Helper function for deducing string literals as std::string
template<typename T>
T make_elem(const T& t) { return t; }

inline std::string make_elem(const char* s) { return std::string(s); }

// make_tuple helper functions
template<typename T1, typename T2, typename T3, typename T4>
auto make_tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4) {
    return Tuple<decltype(make_elem(t1)), 
                decltype(make_elem(t2)), 
                decltype(make_elem(t3)), 
                decltype(make_elem(t4))>
        {make_elem(t1), make_elem(t2), make_elem(t3), make_elem(t4)};
}

template<typename T1, typename T2, typename T3>
auto make_tuple(const T1& t1, const T2& t2, const T3& t3) {
    return Tuple<decltype(make_elem(t1)), 
                decltype(make_elem(t2)), 
                decltype(make_elem(t3))>
        {make_elem(t1), make_elem(t2), make_elem(t3)};
}

template<typename T1, typename T2>
auto make_tuple(const T1& t1, const T2& t2) {
    return Tuple<decltype(make_elem(t1)), 
                decltype(make_elem(t2))>
        {make_elem(t1), make_elem(t2)};
}

template<typename T1>
auto make_tuple(const T1& t1) {
    return Tuple<decltype(make_elem(t1))>{make_elem(t1)};
}

int main() {
    // Create tuples of different sizes
    Tuple<double, int, char> t1{1.1, 42, 'a'};
    
    // Now this works correctly with string literals
    auto t2 = make_tuple(3.14, "Hello");  // t2 will be Tuple<double, std::string>
    
    std::cout << "t1: " << t1 << "\n";
    std::cout << "t2: " << t2 << "\n";
    
    // Access elements
    std::cout << "First element of t2: " << get<0>(t2) << "\n";  // prints 3.14
    std::cout << "Second element of t2: " << get<1>(t2) << "\n"; // prints Hello

    return 0;
}