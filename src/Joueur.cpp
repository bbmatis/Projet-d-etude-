#include "Joueur.h"

unsigned int Joueur::getLifes() const {
    return nb_vies;
}

unsigned int Joueur::setLifes(int life) {
    return nb_vies = life;
}

void Joueur::removesLifes() {
    nb_vies = nb_vies - 1;
}