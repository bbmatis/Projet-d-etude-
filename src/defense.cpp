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

Defense::Defense() //!Constructeur case vide
{
    reloadTime = 0;
    damage = 0;
    zoneDamage = 0;
}
unsigned int Defense::getDamage() const {
    return damage;
}
