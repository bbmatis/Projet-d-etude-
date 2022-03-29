#include "defense.h"

Defense::Defense(typeDef typeDef) {
    type = typeDef;
    zoneDamage = false;
    level = 1;
    switch (type)
    {
        case RIEN: //peut-être créer un type Rien / Null pour dire genre on créer un plateau rempli de déf Null puis 
                   //quand on choisira la déf on changera le type ? 
            damage =0;
            break;
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

Defense::Defense(){};

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
    range = 1;
    // Todo: modifier les valeurs de dégats et de portée et de temps de recharge pourquoi pas
}

// Attaque le/les montres autour d'elle même
void Defense::attackNearby() const {
    // TODO : tout mdr
}


// Obtenir le prix de la défense
unsigned int Defense::getPrix() const {
    return cost;
}