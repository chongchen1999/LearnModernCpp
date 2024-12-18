#include <iostream>
#include <memory>
using namespace std;

// Abstract base class for application interface
class Ival_box {
public:
    virtual ~Ival_box() {}
    virtual void interact() = 0; // Example of an interface method
};

class Ival_slider : public Ival_box {
public:
    virtual ~Ival_slider() {}
};

class Ival_dial : public Ival_box {
public:
    virtual ~Ival_dial() {}
};

// Specialized application classes
class Popup_ival_slider : public Ival_slider {
public:
    void interact() override {
        cout << "Popup slider interacting\n";
    }
};

// User-interface-specific classes
class BBwidget {};
class CWwidget {};

// Concrete implementations for Big Bucks (BB) system
class BB_ival_slider : public Ival_slider, protected BBwidget {
public:
    void interact() override {
        cout << "BB slider interacting\n";
    }
};

class BB_flashing_ival_slider : public Popup_ival_slider, protected BBwidget {
public:
    void interact() override {
        cout << "BB flashing slider interacting\n";
    }
};

class BB_dial : public Ival_dial, protected BBwidget {
public:
    void interact() override {
        cout << "BB dial interacting\n";
    }
};

// Concrete implementations for Cool Widgets (CW) system
class CW_ival_slider : public Ival_slider, protected CWwidget {
public:
    void interact() override {
        cout << "CW slider interacting\n";
    }
};

class CW_popup_ival_slider : public Popup_ival_slider, protected CWwidget {
public:
    void interact() override {
        cout << "CW popup slider interacting\n";
    }
};

class CW_dial : public Ival_dial, protected CWwidget {
public:
    void interact() override {
        cout << "CW dial interacting\n";
    }
};

// Abstract Factory
class Ival_maker {
public:
    virtual ~Ival_maker() {}
    virtual unique_ptr<Ival_dial> dial(int, int) = 0;
    virtual unique_ptr<Popup_ival_slider> popup_slider(int, int) = 0;
};

// Factory for BB system
class BB_maker : public Ival_maker {
public:
    unique_ptr<Ival_dial> dial(int a, int b) override {
        return make_unique<BB_dial>();
    }

    unique_ptr<Popup_ival_slider> popup_slider(int a, int b) override {
        return make_unique<BB_flashing_ival_slider>();
    }
};

// Factory for CW system
class CW_maker : public Ival_maker {
public:
    unique_ptr<Ival_dial> dial(int a, int b) override {
        return make_unique<CW_dial>();
    }

    unique_ptr<Popup_ival_slider> popup_slider(int a, int b) override {
        return make_unique<CW_popup_ival_slider>();
    }
};

// Example usage
void user(Ival_maker& im) {
    unique_ptr<Ival_box> pb = im.dial(0, 99);
    pb->interact(); // Interacts with the created object
}

int main() {
    BB_maker BB_impl;
    CW_maker CW_impl;

    cout << "Using BB implementation:\n";
    user(BB_impl);

    cout << "\nUsing CW implementation:\n";
    user(CW_impl);

    return 0;
}
