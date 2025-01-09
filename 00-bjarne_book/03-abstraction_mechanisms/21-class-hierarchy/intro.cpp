#include <iostream>
#include <string>
#include <stdexcept>

// Base class
class Ival_box {
public:
    virtual ~Ival_box() {}
    virtual void set_value(int value) = 0;
    virtual int get_value() const = 0;
    virtual bool has_changed() const = 0;
};

// Derived class: A simple text-based input box
class Text_box : public Ival_box {
private:
    int value;
    bool changed;

public:
    Text_box() : value(0), changed(false) {}

    void set_value(int new_value) override {
        value = new_value;
        changed = true;
    }

    int get_value() const override {
        return value;
    }

    bool has_changed() const override {
        return changed;
    }

    void reset_changed() {
        changed = false;
    }
};

// Derived class: A slider input
class Slider : public Ival_box {
private:
    int value;
    int min_value;
    int max_value;
    bool changed;

public:
    Slider(int min_val, int max_val)
        : value(min_val), min_value(min_val), max_value(max_val), changed(false) {}

    void set_value(int new_value) override {
        if (new_value < min_value || new_value > max_value)
            throw std::out_of_range("Value out of range");
        value = new_value;
        changed = true;
    }

    int get_value() const override {
        return value;
    }

    bool has_changed() const override {
        return changed;
    }

    void reset_changed() {
        changed = false;
    }
};

// Test the classes
int main() {
    Ival_box* box1 = new Text_box();
    box1->set_value(42);
    std::cout << "Text box value: " << box1->get_value() << "\n";
    std::cout << "Has text box changed? " << box1->has_changed() << "\n";

    Ival_box* slider = new Slider(0, 100);
    slider->set_value(75);
    std::cout << "Slider value: " << slider->get_value() << "\n";
    std::cout << "Has slider changed? " << slider->has_changed() << "\n";

    delete box1;
    delete slider;

    return 0;
}
