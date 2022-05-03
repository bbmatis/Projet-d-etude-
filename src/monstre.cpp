#include "monstre.h"

// Constructeur
Monstre::Monstre(TypeMonstres typeMonstre) {
    type = typeMonstre;
    position.x = 0; // Pour les test en mode graphique
    position.y = 7; // Pour les test en mode graphique

    switch (type)
    {
        case Mob1:
            hp = 50;
            speed = 1;
            break;
        case Mob2:
            hp = 100;
            speed = 1.2;
            break;
        case Mob3:
            hp = 150;
            speed = 0.9;
            break;
    }
}

//constructeur
Monstre::Monstre(){};

// Destructeur
Monstre::~Monstre() {

}

// Déplacer le monstre vers la droite
void Monstre::MoveRight() {
    position.x += speed;
}

// Déplacer le monstre vers la gauche
void Monstre::MoveLeft() {
    position.x -= speed;
}

// Déplacer le monstre vers le haut
void Monstre::MoveUp() {
    position.y -= speed;
}

// Déplacer le monstre vers le bas
void Monstre::MoveDown() {
    position.y += speed;
}

// Obtenir la santée du monstre
int Monstre::getHp() const {
    return hp;
}

// Obtenir la santée max du monstre
int Monstre::getMaxHp() const {
    return maxHp;
}

// Définir la santée du monstre
void Monstre::setHp(int newHp) {
    hp = newHp;
}

// Obtenir la position du monstre
Vecteur2D Monstre::getPosition() const {
    return position;
}

//Définie la position du monstre
void Monstre::setPosition(int new_x, int new_y){
    position.x = new_x;
    position.y = new_y;
}

TypeMonstres Monstre::getType() const{
    return type;
}

// Premier déplacement du monstre
void Monstre::initMonstre(int numeroArriver, int modeAffichage, int vague) {
    // Si en mode graphique
    if (modeAffichage == 1) position.y = 7*37;
    position.x = -numeroArriver * 40;
    setTargetPosition(0, position.y);
    hp+=(vague-1)*hp;
    maxHp = hp;
}

// Définir une position a laquelle le monstre doit se déplacer
void Monstre::setTargetPosition(float x, float y) {
    targetPosition.x = x;
    targetPosition.y = y;
}

// Se déplacer vers la position cible
bool Monstre::moveToTargetPosition() {
    // Si le monstre est au dessus de la position cible
    if (position.y < targetPosition.y) {
        MoveDown();
        if (position.y > targetPosition.y) {
            position.y = targetPosition.y;
        }
    }
    // Si le monstre est au dessous de la position cible
    else if (position.y > targetPosition.y) {
        MoveUp();
        if (position.y < targetPosition.y) {
            position.y = targetPosition.y;
        }
    }

    // Si le monstre est à gauche de la position cible
    if (position.x < targetPosition.x) {
        MoveRight();
        if (position.x > targetPosition.x) {
            position.x = targetPosition.x;
        }
    } else if (position.x > targetPosition.x) {
        MoveLeft();
        if (position.x < targetPosition.x) {
            position.x = targetPosition.x;
        }
    }

    // Si le monstre est à la position cible
    if (position.x == targetPosition.x && position.y == targetPosition.y) {
        return true;
    }

    return false;
}

    

    