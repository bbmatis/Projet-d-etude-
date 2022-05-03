#ifndef MONSTRE_H
#define MONSTRE_H

#include "vecteur2D.h"

enum TypeMonstres {Mob1, Mob2, Mob3};

class Monstre {

    private:
        float speed;            // Vitesse du monstre
        Vecteur2D position;     // Vecteur position (x;y) du monstre
        int hp;                 // Nombre de points de vie du monstre
        int maxHp;              // Nombre maximum de points de vie du monstre
        TypeMonstres type;      // Type du monstre   
    public:

        //! \brief Constructeur
        //! \param type Type du monstre
        Monstre(TypeMonstres type);

        //! \brief Constructeur par défaut
        Monstre();

        //! \brief Destructeur
        ~Monstre();

        //! \brief Déplacer le monstre vers la droite
        void MoveRight(); 

        //! \brief Déplacer le monstre vers la gauche
        void MoveLeft();

        //! \brief Déplacer le monstre vers le haut
        void MoveUp();

        //! \brief Déplacer le monstre vers le bas
        void MoveDown();

        //! \brief Obtenir la santée du monstre
        int getHp() const;

        //! \brief Obtenir la santée max du monstre
        int getMaxHp() const;

        //! \brief Modifier la santée du monstre
        //! \param newHp nouveau nombres de vies
        void setHp(int newHp);

        //! \brief Obtenir la position du monstre
        Vecteur2D getPosition() const;

        //! \brief Modifie la position du montre
        //! \param new_x nouvelle position en x
        //! \param new_y nouvelle position en y
        void setPosition(int new_x, int new_y);

        //! \brief Obtenir le type du monstre
        TypeMonstres getType() const;

        //! \brief Changer la position du monstre
        //! par rapport a son numéro d'arriver dans la vague
        void firstMove(int numeroArriver, int modeDaffichage);
};

#endif