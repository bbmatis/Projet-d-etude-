#include "defense.h"
#include "monstre.h"
#include "Joueur.h"

#define LARGEUR 25
#define HAUTEUR 15




struct Projectile
{
    unsigned int defenseWhoSendMe;
    unsigned int posX, posY;
    float vitesse;
};




class Game {
    private:
        Monstre * monstres;  /** \param monstres Tableau contenant les monstres **/
        Defense * defenses;  /** \param defenses Tableau contenant les défenses **/
        int score;
        Joueur joueur;
        int time;

    public:
        Game(); /** \brief Constructeur **/
        ~Game(); /** \brief Destructeur **/
};