#ifndef GAME_H
#define GAME_H

#include "defense.h"
#include "monstre.h"
#include "joueur.h"

#define LARGEUR 25
#define HAUTEUR 15
#define MAX_MONSTRES 50
#define MAX_PROJECTILES 50

// Définition de la stucture Projectile
struct Projectile
{
    unsigned int defenseWhoSendMe; // Identifie de quelle defense vient le projectile 
    unsigned int posX, posY; // Position du projectil
    float vitesse; // vitesse du projectile
};

class Game {
    private:
        unsigned int score;
        int time;

    public:
        Monstre *monstres;
        Defense *defenses;
        Projectile *projectiles;
        Joueur joueur();
        
        //! \fn Constructeur
        Game();
        
        //! \fn Destructeur
        ~Game();

        //! \fn Initialiser le jeu
        void init();

        void InitVagueMonstre(); //test Initialisation d'une vague de monstre différent

        void InitPlateauJeu(); //test Initialisation du plateau de jeu, rempli de Def et non Null -> affichage texte

        //void AddDefPlateau(Vecteur2D PosDef);

};

#endif