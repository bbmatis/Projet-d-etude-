#include "magasin.h"

/** \brief on appuie sur une case et ça ouvre un menu où on peut cliquer sur une défense à acheter **/
void Magasin::acheterDef(typeDef type) {  
    switch (type) {
        case CANNON:
            money -= 1;
            break;

        case DOUBLECANNON:
            money -= 2;
            break;

        case MORTIER:
            money -= 3;
            break;
    }
}

void Magasin::vendreDef(typeDef type) {
    switch (type) {
        case CANNON:
            money += 1;
            break;

        case DOUBLECANNON:
            money += 2;
            break;

        case MORTIER:
            money += 3;
            break;
    }
}

unsigned int Magasin::getMoney() const {
    return money;
}

unsigned int Magasin::addMoney(TypeMonstres type) {
    switch (type)
    {
        case Mob1:
            money += 1;
            break;

        case Mob2:
            money += 2;
            break;

        case Mob3:
            money += 3;
            break;
    }

    return money;
}


// les set marche pas zebi
void Magasin::acheterImproveDef(typeDef type , Defense d) {
    switch (type) {
        case CANNON:
            money -= 1;
            d.setReloadTime(0.25f);
            break;

        case DOUBLECANNON:
            money -= 2;
            d.setDamage(100);
            d.setZoneDamage(true);
            break;
    }
}