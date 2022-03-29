#include "joueur.h"

// Constructeur
Joueur::Joueur() {
    nbVies = 3;
    money = 200;
}

// Destructeur
Joueur::~Joueur() {
}

// Obtenir le nombre de vies du joueur
unsigned int Joueur::getNbVies() const {
    return nbVies;
}

// Modifier le nombre de vies du joueur
void Joueur::setNbVies(unsigned int newNbVies) {
    nbVies = newNbVies;
}

