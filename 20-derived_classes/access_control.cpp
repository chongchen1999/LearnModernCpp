#include <iostream>
#include <list>
#include <stdexcept>
#include <initializer_list>

class Shape {
public:
    virtual void rotate(int) = 0;  // Pure virtual function
    virtual void draw() const = 0; // Pure virtual function
    virtual bool is_closed() const = 0; // Pure virtual function
    virtual ~Shape() = default;   // Virtual destructor
};

class Point {
    // Placeholder for Point class
};

class Circle : public Shape {
public:
    void rotate(int) override {}
    void draw() const override {}
    bool is_closed() const override { return true; }
    Circle(Point p, int r) : center(p), radius(r) {}
private:
    Point center;
    int radius;
};

class Polygon : public Shape {
public:
    bool is_closed() const override { return true; }
    // draw() and rotate() not overridden, so still abstract
};

class Irregular_polygon : public Polygon {
    std::list<Point> lp;
public:
    Irregular_polygon(std::initializer_list<Point> points) : lp(points) {}
    void draw() const override {}
    void rotate(int) override {}
};

class Character_device {
public:
    virtual int open(int opt) = 0;
    virtual int close(int opt) = 0;
    virtual int read(char* p, int n) = 0;
    virtual int write(const char* p, int n) = 0;
    virtual int ioctl(int opt...) = 0;
    virtual ~Character_device() = default;
};

template<class T>
class List {
public:
    void insert(T val);
    T get();
private:
    struct Link { T val; Link* next; };
    struct Chunk {
        enum { chunk_size = 15 };
        Link v[chunk_size];
        Chunk* next;
    };
    Chunk* allocated = nullptr;
    Link* free = nullptr;
    Link* head = nullptr;

    Link* get_free();
};

template<class T>
void List<T>::insert(T val) {
    Link* lnk = get_free();
    lnk->val = val;
    lnk->next = head;
    head = lnk;
}

template<class T>
T List<T>::get() {
    if (head == nullptr)
        throw std::underflow_error("Underflow");
    Link* p = head;
    head = p->next;
    p->next = free;
    free = p;
    return p->val;
}

template<class T>
typename List<T>::Link* List<T>::get_free() {
    if (free == nullptr) {
        // Allocate a new chunk and populate free list
    }
    Link* p = free;
    free = free->next;
    return p;
}

int main() {
    // Example usage
    Point p1, p2, p3, p4;
    Irregular_polygon poly{p1, p2, p3, p4};
    return 0;
}
