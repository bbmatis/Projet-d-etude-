#include "defense.h"

Defense::Defense(typeDef type) {
    zoneDamage = false;
    switch (type)
    {
        case CANNON:
            reloadTime = 0.5f;
            damage = 5;
            break;
        case DOUBLECANNON:
            reloadTime = 0.25f;
            damage = 5;
            break;
        case MORTIER:
            reloadTime = 2.0f;
            damage = 100;
            zoneDamage = true;
            break;
    }
}

unsigned int Defense::setDamage(unsigned int new_damage) {
    return damage = new_damage;
}

bool Defense::setZoneDamage(bool new_zoneDamage) {
    return zoneDamage = new_zoneDamage;
}

float Defense::setReloadTime(float new_reloadTime) {
    return reloadTime = new_reloadTime;
}

unsigned int Defense::getDamage() const {
    return damage;
}

float Defense::getReloadTime() const {
    return reloadTime;
}

bool Defense::getZoneDamage() const {
    return zoneDamage;
}


