#include "monstre.h"


Monstre::Monstre(TypeMonstres type, Vecteur2D PosInit) {
    
    switch (type)
    {
        case Mob1:
            nb_vie = 50;
            speed = 2;
            break;
        case Mob2:
            nb_vie = 150;
            speed = 2;
            break;
        case Mob3:
            nb_vie = 50;
            speed = 2;
            break;
    }
}

Monstre::~Monstre(){
}

Vecteur2D Monstre::getPos()
{
    return position;
}

void Monstre::MoveRight(){

    position.x += speed;

}

void Monstre::MoveLeft(){

    position.x -= speed;

}

void Monstre::MoveUp(){

    position.y += speed;

}
void Monstre::MoveDown(){

    position.y -= speed;

}

unsigned int Monstre::getLife(){
    return nb_vie;
}


void Monstre::removeLife(int nb)
{
    nb_vie -= nb;
}
