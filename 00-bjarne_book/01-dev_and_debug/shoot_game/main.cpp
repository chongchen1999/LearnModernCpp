#include "gun.h"
#include "solider.h"

int main() {
    Gun* gun = new Gun("rifle");
    Solider* solider = new Solider("Mike");
    solider->addGun(gun);
    solider->addBulletToGun(10);
    for (int i = 0; i < 15; i++) {
        solider->fire();
    }
    delete solider;
    return 0;
}