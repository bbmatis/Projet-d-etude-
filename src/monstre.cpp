#include "monstre.h"

// Constructeur
Monstre::Monstre(TypeMonstres type) {
    
    switch (type)
    {
        case Mob1:
            hp = 50;
            speed = 2;
            break;
        case Mob2:
            hp = 150;
            speed = 2;
            break;
        case Mob3:
            hp = 50;
            speed = 2;
            break;
    }
}

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
unsigned int Monstre::getHp() const {
    return hp;
}

// Définir la santée du monstre
void Monstre::setHp(unsigned int newHp) {
    hp = newHp;
}

// Obtenir la position du monstre
Vecteur2D Monstre::getPosition() const {
    return position;
}
