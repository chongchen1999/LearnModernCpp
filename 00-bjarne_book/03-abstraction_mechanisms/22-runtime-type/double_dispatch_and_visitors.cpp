#include <iostream>
#include <vector>
#include <utility>

// Double Dispatch Section
class Circle;
class Triangle;

class Shape {
public:
    virtual bool intersect(const Shape&) const = 0;
    virtual bool intersect(const Circle&) const = 0;
    virtual bool intersect(const Triangle&) const = 0;
};

class Circle : public Shape {
public:
    bool intersect(const Shape& s) const override { return s.intersect(*this); }
    bool intersect(const Circle&) const override {
        std::cout << "intersect(circle, circle)\n";
        return true;
    }
    bool intersect(const Triangle&) const override {
        std::cout << "intersect(circle, triangle)\n";
        return true;
    }
};

class Triangle : public Shape {
public:
    bool intersect(const Shape& s) const override { return s.intersect(*this); }
    bool intersect(const Circle&) const override {
        std::cout << "intersect(triangle, circle)\n";
        return true;
    }
    bool intersect(const Triangle&) const override {
        std::cout << "intersect(triangle, triangle)\n";
        return true;
    }
};

void test_double_dispatch(Triangle& t, Circle& c) {
    std::vector<std::pair<Shape*, Shape*>> shapes = { {&t, &t}, {&t, &c}, {&c, &t}, {&c, &c} };
    for (const auto& p : shapes) {
        p.first->intersect(*p.second);
    }
}

// Visitor Pattern Section
class Visitor;

class Node {
public:
    virtual void accept(Visitor&) = 0;
};

class Expr : public Node {
public:
    void accept(Visitor& v) override;
};

class Stmt : public Node {
public:
    void accept(Visitor& v) override;
};

class Visitor {
public:
    virtual void accept(Expr&) = 0;
    virtual void accept(Stmt&) = 0;
};

class Do1Visitor : public Visitor {
public:
    void accept(Expr&) override { std::cout << "do1 to Expr\n"; }
    void accept(Stmt&) override { std::cout << "do1 to Stmt\n"; }
};

class Do2Visitor : public Visitor {
public:
    void accept(Expr&) override { std::cout << "do2 to Expr\n"; }
    void accept(Stmt&) override { std::cout << "do2 to Stmt\n"; }
};

void Expr::accept(Visitor& v) { v.accept(*this); }
void Stmt::accept(Visitor& v) { v.accept(*this); }

void test_visitors(Expr& e, Stmt& s) {
    Do1Visitor do1;
    Do2Visitor do2;
    std::vector<std::pair<Node*, Visitor*>> tasks = { {&e, &do1}, {&s, &do1}, {&e, &do2}, {&s, &do2} };
    for (auto& task : tasks) {
        task.first->accept(*task.second);
    }
}

int main() {
    Triangle t;
    Circle c;
    test_double_dispatch(t, c);

    Expr e;
    Stmt s;
    test_visitors(e, s);

    return 0;
}
