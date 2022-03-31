#include "joueur.h"
#include <time.h>

// Constructeur
Joueur::Joueur() {
    nbVies = 3;
    money = 200;
    score = clock();
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

// Obtenir le score du joueur
unsigned int Joueur::getScore() const {
    return score;
}

// Modifier le score du joueur
void Joueur::setScore(unsigned int newScore) {
    score = newScore;
}
