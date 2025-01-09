#pragma once

#include <string>
#include "gun.h"

class Solider {
public:
    Solider();
    Solider(std::string name);
    Solider(std::string name, Gun* gun);
    ~Solider();

    void addGun(Gun* gun);
    void addBulletToGun(int num);
    bool fire();

private:
    std::string name;
    Gun* gun;
};