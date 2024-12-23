#include <memory>
#include <iostream>
#include <string>
#include <vector>

using namespace  std;

// unique_ptr examples
unique_ptr<int> f(unique_ptr<int> p) {
    ++*p;
    return p;
}

void f2(const unique_ptr<int>& p) {
    ++*p;
}

void use() {
    unique_ptr<int> p {new int{7}};
    // p = f(p); // error : no copy constructor
    p = f(std::move(p)); // transfer ownership there and back
    f2(p); // pass a reference
    std::cout << *p << std::endl;
}

// shared_ptr examples
struct S {
    int i;
    std::string s;
    double d;
};

struct Asteroid;

// weak_ptr examples in an asteroid game - like scenario
void collision(std::weak_ptr<Asteroid> p) {
    if (auto q = p.lock()) {
        // p.lock returns a shared_ptr to p’s object
        std::cout << "Collision calculation, asteroid still exists" << std::endl;
    }
    else {
        // Oops: that Asteroid has already been destroyed
        p.reset();
        std::cout << "Asteroid already destroyed" << std::endl;
    }
}

struct Asteroid {
    std::weak_ptr<Asteroid> neighbor;
    Asteroid(std::weak_ptr<Asteroid> n) : neighbor(n) {}
};

void owner() {
    std::vector<std::shared_ptr<Asteroid>> va(100);
    for (int i = 0; i < va.size(); ++i) {
        // Simplified neighbor calculation, giving each new Asteroid just one neighbor
        int neighborIndex = (i + 1) % va.size();
        va[i].reset(new Asteroid(std::weak_ptr<Asteroid>(va[neighborIndex])));
        // launch(i); // Simplified launch function, not implemented here
    }
    // Simulate a collision
    collision(va[0]->neighbor);
}

int main() {
    use();
    auto p = std::make_shared<S>(1, "Ankh Morpork", 4.65);
    std::cout << p->i << " " << p->s << " " << p->d << std::endl;
    owner();
    return 0;
}