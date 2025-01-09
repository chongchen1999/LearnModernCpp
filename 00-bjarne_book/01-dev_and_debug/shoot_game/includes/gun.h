#pragma once
#include <string>

class Gun {
public:
    Gun();
    Gun(std::string type);

    void addBiullet(int count);
    bool shoot();

private:
    int bulllet_count;
    std::string type_;
};