#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <string>

struct Io_obj {
    virtual ~Io_obj() = default;
    virtual Io_obj* clone() const = 0;
};

template <typename T>
struct Io : public T, public virtual Io_obj {
    Io_obj* clone() const override {
        return new Io{*this};
    }
};

struct Circle {};
struct Io_circle : public Io<Circle> {
    static Io_obj* new_io(std::istream&) {
        return new Io_circle{};
    }
};

std::map<std::string, Io_obj* (*)(std::istream&)> io_map;

Io_obj* get_obj(std::istream& is) {
    std::string name;
    is >> name;
    return io_map[name](is);
}

int main() {
    io_map["Circle"] = &Io_circle::new_io;

    std::istringstream ss("Circle");
    std::unique_ptr<Io_obj> obj(get_obj(ss));
    return 0;
}
