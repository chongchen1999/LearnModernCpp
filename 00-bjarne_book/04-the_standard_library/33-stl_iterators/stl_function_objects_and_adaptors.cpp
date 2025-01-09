#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

// Function for bind example
void f(int a, const std::string& b) {
    std::cout << "a: " << a << ", b: " << b << std::endl;
}

// Shape class for mem_fn example
class Shape {
public:
    void draw() {
        std::cout << "Drawing a shape" << std::endl;
    }
};

// Function to draw all shapes using mem_fn
void draw_all(std::vector<Shape*>& v) {
    for_each(v.begin(), v.end(), std::mem_fn(&Shape::draw));
}

// Function for std::function example
int round_(double x) {
    return static_cast<int>(std::floor(x + 0.5));
}

int main() {
    // Predicates example
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::sort(v.begin(), v.end(), std::greater<int>());
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Arithmetic Operations example
    std::plus<int> add;
    int result = add(3, 5);
    std::cout << "3 + 5 = " << result << std::endl;

    // bind() example
    using namespace std::placeholders;
    auto g = std::bind(f, 2, _1);
    g("hello");

    // mem_fn() example
    std::vector<Shape*> v_shapes;
    v_shapes.push_back(new Shape());
    draw_all(v_shapes);
    for (Shape* s : v_shapes) {
        delete s;
    }

    // std::function example
    std::function<int(double)> fct;
    fct = round_;
    std::cout << fct(7.6) << std::endl;
    fct = [](double x) { return static_cast<int>(x); };
    std::cout << fct(7.6) << std::endl;

    return 0;
}