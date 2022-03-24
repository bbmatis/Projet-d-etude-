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


struct Vecteur2D
{
    float x,y;

    const &operator +(const opérande_D) {
       x = x + opérande_D.x;
    }
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