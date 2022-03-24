#include "defense.h"
#include "monstre.h"
#include "Joueur.h"

#define LARGEUR 25
#define HAUTEUR 15




struct Projectile
{
    unsigned int defenseWhoSendMe; /** \param defenseWhoSendMe identifie de quelle defense vient le projectile **/
    unsigned int posX, posY; /** \param posX position en x du projectile
                                 \param posY position en y du projectile **/
    float vitesse; /** \param vitesse vitesse du projectile **/
};




class Game {
    private:
        
        int score;
        Joueur joueur;
        int time;

    public:
        Monstre * monstres;/** \param monstres Tableau contenant les monstres **/
        Defense * defenses;  /** \param defenses Tableau contenant les défenses **/
        Game(); /** \brief Constructeur **/
        ~Game(); /** \brief Destructeur **/
        void DefineMonstres();
};