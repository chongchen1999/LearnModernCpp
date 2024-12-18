#include <iostream>
#include <typeinfo> // For std::bad_cast

// Base classes and interfaces
class BBwindow {
public:
    virtual ~BBwindow() = default; // Virtual destructor for polymorphic behavior
};

class Ival_box : public virtual BBwindow { // Virtual inheritance
public:
    virtual int get_value() const = 0; // Pure virtual function
};

class Ival_slider : public virtual Ival_box { // Virtual inheritance
public:
    int get_value() const override { return 42; } // Example implementation
};

class BBslider : public virtual BBwindow { // Virtual inheritance
    // Additional members can go here
};

class BB_ival_slider : public Ival_slider, public BBslider { 
    // Now BBwindow is virtually inherited, so there's no ambiguity
};

// Event handler using dynamic_cast
void my_event_handler(BBwindow* pw) {
    if (auto pb = dynamic_cast<Ival_box*>(pw)) {
        int x = pb->get_value(); 
        std::cout << "Value: " << x << std::endl;
    } else {
        std::cerr << "Invalid type!" << std::endl;
    }
}

// Function demonstrating dynamic_cast and exception handling for references
void fr(Ival_box& r) {
    try {
        Ival_slider& is = dynamic_cast<Ival_slider&>(r);
        std::cout << "Reference to Ival_slider obtained successfully.\n";
    } catch (const std::bad_cast& e) {
        std::cerr << "Bad cast: " << e.what() << std::endl;
    }
}

// Main function to test the concepts
int main() {
    BB_ival_slider slider;
    my_event_handler(&slider); // Expected to be valid

    try {
        fr(slider); // Expected to be valid as well
    } catch (const std::bad_cast& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}
