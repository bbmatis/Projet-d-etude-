#include "defense.h"

Defense::Defense(typeDef type) {
    zoneDamage = false;
    level = 1;
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


// Définir les dégats de la défense
void Defense::setDamage(unsigned int newDamage) {
    damage = newDamage;
}

// Obtenir les dégats que fait la defense
unsigned int Defense::getDamage() const {
    return damage;
}

// Définir le temps de recharge de la defense
void Defense::setReloadTime(float newReloadTime) {
    reloadTime = newReloadTime;
}

// Obtenir le temps de recharge de la defense
float Defense::getReloadTime() const {
    return reloadTime;
}

// Définir la portée de la défense
void Defense::setRange(unsigned int newRange) {
    range = newRange;
}

// Obtenir la portée de la défense
unsigned int Defense::getRange() const {
    return range;
}

// Améliorer la défense au niveau supérieur
void Defense::Ameliorer() {
    level++;
    // Todo: modifier les valeurs de dégats et de portée
}

// Attaque le/les montres autour d'elle même
void Defense::attackNearby() const {
    // TODO
}