#include "monstre.h"

// Constructeur
Monstre::Monstre(TypeMonstres type) {
    position.x = 0;
    position.y = 7;

    switch (type)
    {
        case Mob1:
            hp = 50;
            speed = 1;
            break;
        case Mob2:
            hp = 100;
            speed = 1;
            break;
        case Mob3:
            hp = 150;
            speed = 1;
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

