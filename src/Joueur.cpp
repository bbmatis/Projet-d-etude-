#include "Joueur.h"

// Constructeur
Joueur::Joueur() {
    nbVies = 3;
}

// Obtenir le nombre de vies du joueur
unsigned int Joueur::getNbVies() const {
    return nbVies;
}

// Modifier le nombre de vies du joueur
void Joueur::setNbVies(unsigned int newNbVies) {
    nbVies = newNbVies;
}

