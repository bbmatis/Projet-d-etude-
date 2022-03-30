#ifndef MONSTRE_H
#define MONSTRE_H

#include "vecteur2D.h"

enum TypeMonstres {Mob1, Mob2, Mob3};

class Monstre {

    private:
        float speed;            /** \param speed Vitesse du monstre **/
        Vecteur2D position;     /** \param position Vecteur position (x;y) du monstre**/
        unsigned int hp;        /** \param hp Nombre de points de vie du monstre**/
     
    public:
        //! \fn Constructeur
        //! \param type Type du monstre
        Monstre(TypeMonstres type);

        //! \fn Constructeur par défaut
        Monstre();

        //! \fn Destructeur
        ~Monstre();

        //! \fn Déplacer le monstre vers la droite
        void MoveRight(); 

        //! \fn Déplacer le monstre vers la gauche
        void MoveLeft();

        //! \fn Déplacer le monstre vers le haut
        void MoveUp();

        //! \fn Déplacer le monstre vers le bas
        void MoveDown();

        //! \fn Obtenir la santée du monstre
        unsigned int getHp() const;

        //! \fn Modifier la santée du monstre
        void setHp(unsigned int newHp);

        //! \fn Obtenir la position du monstre
        Vecteur2D getPosition() const;

        //! \fn Modifie la position du montre
        void setPosition(int new_x, int new_y);

       
};

#endif