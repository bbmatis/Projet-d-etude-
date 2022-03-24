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

void Monstre::MoveRight(Vecteur2D pos2){

    position.x += pos2.x;

}

void Monstre::MoveLeft(Vecteur2D pos2){

    position.x -= pos2.x;

}

void Monstre::MoveUp(Vecteur2D pos2){

    position.y += pos2.y;

}
void Monstre::MoveDown(Vecteur2D pos2){

    position.y -= pos2.y;

}

unsigned int Monstre::getLife(){
    return nb_vie;
}


void Monstre::removeLife(int nb)
{
    nb_vie -= nb;
}

