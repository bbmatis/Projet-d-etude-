#ifndef GAME_H
#define GAME_H

#include "defense.h"
#include "monstre.h"
#include "joueur.h"
#include <vector>

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
        vector<Monstre> monstres;
        vector<Defense> defenses;
        vector<Projectile> projectiles;
        
        Joueur joueur;
        

        //! \fn Constructeur
        Game();
        
        //! \fn Destructeur
        ~Game();

        //! \fn Initialiser le jeu
        void init();

        void InitVagueMonstre(); //test Initialisation d'une vague de monstre différent

        void InitPlateauJeu(); //test Initialisation du plateau de jeu, rempli de Def et non Null -> affichage texte

        //void AddDefPlateau(Vecteur2D PosDef);

        //! \fn Acheter une défense
        //! \param type type de défense à acheter
        void buyDef(typeDef type);

        //! \fn vendre une défense
        //! \param defense défense à vendre
        void sellDef(Defense defense);

        //! \fn Améliorer une défense
        //! \param defense défense à améliorer
        void upgradeDef(Defense defense);

};

#endif