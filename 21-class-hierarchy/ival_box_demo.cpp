#include <iostream>
#include <memory>

// Abstract base interface class
class Ival_box {
public:
    virtual int get_value() = 0;
    virtual void set_value(int i) = 0;
    virtual void reset_value(int i) = 0;
    virtual void prompt() = 0;
    virtual bool was_changed() const = 0;
    virtual ~Ival_box() = default;
};

// Concrete implementation using composition
class Ival_box_impl : public Ival_box {
private:
    int val;
    int low, high;
    bool changed{false};

public:
    Ival_box_impl(int ll, int hh) : val{ll}, low{ll}, high{hh} {}

    int get_value() override {
        prompt();
        return val;
    }

    void set_value(int i) override {
        if (i >= low && i <= high) {
            val = i;
            changed = true;
        }
    }

    void reset_value(int i) override {
        if (i >= low && i <= high) {
            val = i;
            changed = false;
        }
    }

    void prompt() override {
        std::cout << "Please input a value between " << low << " and " << high << ".\n";
    }

    bool was_changed() const override { 
        return changed; 
    }
};

// Slider implementation with specific behavior
class Ival_slider : public Ival_box {
private:
    int val;
    int low, high;
    bool changed{false};

public:
    Ival_slider(int ll, int hh) : val{ll}, low{ll}, high{hh} {}

    int get_value() override {
        prompt();
        val = (low + high) / 2;  // Auto-select middle value
        return val;
    }

    void set_value(int i) override {
        if (i >= low && i <= high) {
            val = i;
            changed = true;
        }
    }

    void reset_value(int i) override {
        if (i >= low && i <= high) {
            val = i;
            changed = false;
        }
    }

    void prompt() override {
        std::cout << "Slider: Choose a value between " << low << " and " << high << ".\n";
    }

    bool was_changed() const override { 
        return changed; 
    }
};

// Shared interaction function using abstract base class
void interact(Ival_box& pb) {
    pb.prompt();
    int i = pb.get_value();
    if (pb.was_changed()) {
        std::cout << "Value was changed to: " << i << "\n";
    } else {
        std::cout << "Value was not changed.\n";
    }
}

int main() {
    // Demonstration of implementation inheritance
    std::cout << "Demo: Implementation Inheritance\n";
    Ival_box_impl slider1(0, 10);
    interact(slider1);

    std::cout << "\nDemo: Interface Implementation\n";
    Ival_slider slider2(0, 10);
    interact(slider2);

    return 0;
}