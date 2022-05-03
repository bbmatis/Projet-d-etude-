#ifndef MONSTRE_H
#define MONSTRE_H

#include "vecteur2D.h"

enum TypeMonstres {Mob1, Mob2, Mob3};

class Monstre {

    private:
        TypeMonstres type;      // Type du monstre   
        float speed;            // Vitesse du monstre
        Vecteur2D position;     // Vecteur position (x;y) du monstre
        int hp;                 // Nombre de points de vie du monstre
        int maxHp;              // Nombre maximum de points de vie du monstre
        Vecteur2D targetPosition; // Vecteur position (x;y) ou le monstre doit se rendre
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

        //! \brief Définir une position a laquelle le monstre doit se déplacer
        //! \param x Position en x
        //! \param y Position en y
        void setTargetPosition(float x, float y);

        //! \brief Se déplacer vers la position cible
        //! \return true si le monstre a atteint sa cible
        bool moveToTargetPosition();

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

        //! \brief Initialise le monstre
        //! par rapport a son numéro d'arriver dans la vague
        void initMonstre(int numeroArriver, int modeDaffichage, int vague);
};

#endif