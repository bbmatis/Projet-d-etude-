#include "defense.h"

Defense::Defense(typeDef typeDef) {
    type = typeDef;
    level = 1;
    lastHit = 0;
    switch (type)
    {
        case CANON:
            reloadTime = 0.5f;
            damage = 5;
            range = 3;
            prix = 50;
            break;
        case DOUBLECANON:
            reloadTime = 0.25f;
            damage = 10;
            range = 2;
            prix = 100;
            break;
        case MORTIER:
            reloadTime = 2.0f;
            damage = 25;
            range = 4;
            prix = 200;
            break;
        default:
            break;
    }
}

Defense::Defense(){
    type = RIEN;
    level = 0;
    reloadTime = 0.0f;
    damage = 0;
};

Defense::~Defense(){};

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

// Récuper le type de la défense
typeDef Defense::getType() const {
    return type;
}

// Améliorer la défense au niveau supérieur
void Defense::upgrade() {
    level++;
    damage += 5;
    range += 1;
    // Todo: modifier les valeurs de temps de recharge pourquoi pas
}



// Obtenir le prix de la défense
unsigned int Defense::getPrix() const {
    return prix;
}

// Obtenir le lvl de la défense
unsigned int Defense::getLevel() const {
    return level;
}

// Définir la dernière frappe
void Defense::setLastHit(unsigned int newLastHit) {
    lastHit = newLastHit;
}

// Récuper le dernier temps de frappe
unsigned int Defense::getLastHit() const {
    return lastHit;
}