#include "joueur.h"

// Constructeur
Joueur::Joueur() {
    nbVies = 3;
    money = 500;
    score = 0;
}

// Destructeur
Joueur::~Joueur() {
}

// Obtenir le nombre de vies du joueur
int Joueur::getNbVies() const {
    return nbVies;
}

// Modifier le nombre de vies du joueur
void Joueur::setNbVies(int newNbVies) {
    nbVies = newNbVies;
}

// Obtenir le score du joueur
int Joueur::getScore() const {
    return score;
}

// Modifier le score du joueur
void Joueur::setScore(unsigned int newScore) {
    score = newScore;
}

// Obtenir le nom du joueur
string Joueur::getNom() const {
    return nom;
}

// Modifier le nom du joueur
void Joueur::setNom(string newNom) {
    nom = newNom;
}

// Remet a 0 le joeuur
void Joueur::reset() {
    nbVies = 3;
    money = 500;
    score = 0;
}