#include "gun.h"
#include <iostream>

Gun::Gun() : bulllet_count(0), type_{"pistol"} {}
Gun::Gun(std::string type) : bulllet_count(0), type_{type} {}

void Gun::addBiullet(int count) {
    bulllet_count += count;
}

bool Gun::shoot() {
    if (bulllet_count > 0) {
        bulllet_count--;
        std::cout << "Bang! " << "remaining bullets: " << bulllet_count << std::endl;
        return true;
    } else {
        std::cout << "Click!" << std::endl;
        return false;
    }
}