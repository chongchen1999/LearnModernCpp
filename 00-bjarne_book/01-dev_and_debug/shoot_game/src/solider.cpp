#include "solider.h"
#include <iostream>

Solider::Solider() : name{"John"}, gun{} {}
Solider::Solider(std::string name) : name{name}, gun{} {}
Solider::Solider(std::string name, Gun* gun) : name{name}, gun{gun} {}
Solider::~Solider() {
    if (gun) {
        delete gun;
        gun = nullptr;
    }
}

void Solider::addGun(Gun* gun) {
    this->gun = gun;
}

void Solider::addBulletToGun(int num) {
    if (gun) {
        gun->addBiullet(num);
    } else {
        std::cout << "No gun!" << std::endl;
    }
}

bool Solider::fire() {
    if (gun) {
        return gun->shoot();
    } else {
        return false;
    }
}