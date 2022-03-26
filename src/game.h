#include "defense.h"
#include "monstre.h"
#include "Joueur.h"

#define LARGEUR 25
#define HAUTEUR 15
#define MAX_MONSTRES 50
#define MAX_PROJECTILES 50

// Définition de la stucture Projectile
struct Projectile
{
    unsigned int defenseWhoSendMe; /** \param defenseWhoSendMe identifie de quelle defense vient le projectile **/
    unsigned int posX, posY; /** \param posX position en x du projectile
                                 \param posY position en y du projectile **/
    float vitesse; /** \param vitesse vitesse du projectile **/
};

class Game {
    private:
        unsigned int score;
        Joueur joueur();
        int time;

    public:
        Monstre *monstres;
        Defense *defenses;
        Projectile *projectiles;
        
        //! \fn Constructeur
        Game();
        
        //! \fn Destructeur
        ~Game();

        //! \fn Initialiser le jeu
        void init();

        //! \fn getScore
        unsigned int getScore();

        //! \fn setScore
        void setScore(unsigned int new_score);

        void InitVagueMonstre(); //test Initialisation d'une vague de monstre différent

        void InitPlateauJeu(); //test Initialisation du plateau de jeu, rempli de Def et non Null -> affichage texte

        void CasePlateauEstVide(); //Dcp regarde si la case du plateau est une def Null ou non 

        //void AddDefPlateau(Vecteur2D PosDef);

};