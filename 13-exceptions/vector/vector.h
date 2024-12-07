#include <memory>
#include <algorithm>
#include <utility>

template<class T, class A = std::allocator<T>>
class vector {
private:
    template<class U, class B = std::allocator<U>>
    struct vector_base {
        B alloc;
        U* elem;   // Start of allocation
        U* space;  // End of element sequence
        U* last;   // End of allocated space

        vector_base(const B& a, typename B::size_type n)
            : alloc{a}, elem{alloc.allocate(n)}, space{elem}, last{elem + n} {}

        ~vector_base() { 
            if (elem) alloc.deallocate(elem, last - elem); 
        }

        vector_base(vector_base&& a)
            : alloc{std::move(a.alloc)}, elem{a.elem}, space{a.space}, last{a.last} {
            a.elem = a.space = a.last = nullptr;
        }

        vector_base& operator=(vector_base&& a) {
            std::swap(alloc, a.alloc);
            std::swap(elem, a.elem);
            std::swap(space, a.space);
            std::swap(last, a.last);
            return *this;
        }

        // Prevent copying
        vector_base(const vector_base&) = delete;
        vector_base& operator=(const vector_base&) = delete;
    };

    template<typename In, typename Out>
    static Out uninitialized_move(In b, In e, Out oo) {
        for (; b != e; ++b, ++oo) {
            new(static_cast<void*>(&*oo)) T{std::move(*b)};
            b->~T();
        }
        return oo;
    }

    template<typename In>
    static void destroy(In b, In e) {
        for (; b != e; ++b)
            b->~T();
    }

    vector_base<T, A> vb;

public:
    using size_type = unsigned int;

    vector() : vb{A(), 0} {} // Default constructor

    explicit vector(size_type n, const T& val = T(), const A& a = A())
        : vb{a, n} {
        std::uninitialized_fill(vb.elem, vb.elem + n, val);
        vb.space = vb.elem + n;
    }

    vector(const vector& a)
        : vb{a.vb.alloc, a.size()} {
        std::uninitialized_copy(a.begin(), a.end(), vb.elem);
        vb.space = vb.elem + a.size();
    }

    vector& operator=(const vector& a) {
        vector temp{a};
        std::swap(*this, temp);
        return *this;
    }

    vector(vector&& a)
        : vb{std::move(a.vb)} {}

    vector& operator=(vector&& a) {
        std::swap(vb, a.vb);
        return *this;
    }

    ~vector() { 
        destroy(vb.elem, vb.space);
    }

    size_type size() const { return vb.space - vb.elem; }
    size_type capacity() const { return vb.last - vb.elem; }

    void reserve(size_type newalloc) {
        if (newalloc <= capacity()) return;
        vector_base<T, A> b{vb.alloc, newalloc};
        T* new_space = uninitialized_move(vb.elem, vb.space, b.elem);
        destroy(vb.elem, vb.space);
        vb = std::move(b);
        vb.space = new_space;
    }

    void resize(size_type newsize, const T& val = T()) {
        reserve(newsize);
        if (size() < newsize)
            std::uninitialized_fill(vb.elem + size(), vb.elem + newsize, val);
        else
            destroy(vb.elem + newsize, vb.elem + size());
        vb.space = vb.elem + newsize;
    }

    void push_back(const T& x) {
        if (capacity() == size())
            reserve(size() ? 2 * size() : 8);
        vb.alloc.construct(vb.space, x);
        ++vb.space;
    }

    T* begin() { return vb.elem; }
    const T* begin() const { return vb.elem; }
    T* end() { return vb.space; }
    const T* end() const { return vb.space; }
};
