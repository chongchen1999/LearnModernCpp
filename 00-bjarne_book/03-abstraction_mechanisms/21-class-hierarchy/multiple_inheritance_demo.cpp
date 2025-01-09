#include <iostream>
#include <string>

// Abstract interface for storable objects
class Storable {
   public:
    virtual std::string get_file() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
    virtual ~Storable() = default;
};

// Abstract interface for displayable objects
class Displayable {
   public:
    virtual void draw() = 0;
    virtual void set_color(const std::string& color) = 0;
    virtual ~Displayable() = default;
};

// Concrete implementation of a communication device
class CommunicationDevice : public Storable, public Displayable {
   private:
    std::string file_name;
    std::string color;

   public:
    CommunicationDevice(const std::string& filename)
        : file_name(filename), color("white") {}

    // Storable interface implementation
    std::string get_file() override { return file_name; }
    void read() override {
        std::cout << "Reading device data from " << file_name << std::endl;
    }
    void write() override {
        std::cout << "Writing device data to " << file_name << std::endl;
    }

    // Displayable interface implementation
    void draw() override {
        std::cout << "Drawing device in " << color << std::endl;
    }
    void set_color(const std::string& new_color) override { color = new_color; }
};

// Specialized radio class with multiple inheritance
class Radio : public CommunicationDevice {
   private:
    double frequency;

   public:
    Radio(const std::string& filename, double freq)
        : CommunicationDevice(filename), frequency(freq) {}

    // Demonstrate method overriding and calling base implementations
    void write() override {
        CommunicationDevice::write();
        std::cout << "Writing additional radio-specific data" << std::endl;
    }

    void describe() {
        std::cout << "Radio frequency: " << frequency << " MHz" << std::endl;
    }
};

int main() {
    Radio myRadio("radio_data.txt", 99.5);

    // Demonstrate multiple inheritance capabilities
    myRadio.set_color("red");
    myRadio.draw();
    myRadio.write();
    myRadio.read();
    myRadio.describe();

    return 0;
}