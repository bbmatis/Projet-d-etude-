#ifndef GAME_H
#define GAME_H

#include "defense.h"
#include "monstre.h"
#include "joueur.h"
#include "vecteur2D.h"
#include <vector>

#define LARGEUR 25
#define HAUTEUR 15
#define MAX_MONSTRES 50
#define MAX_PROJECTILES 50

// Définition de la stucture Projectile
struct Projectile
{
    unsigned int defenseWhoSendMe; // Identifie de quelle defense vient le projectile 
    Vecteur2D position; // Position du projectil
    float vitesse; // vitesse du projectile
};

class Game {
    private:
        unsigned int score;
        int time;

        //! \fn Acheter une défense
        //! \param type type de défense à acheter
        void buyDef(typeDef type);

        float Distance(int x1, int y1, int x2, int y2);
               

    public:
        std::vector<Monstre> monstres;
        std::vector<Defense> defenses;
        std::vector<Projectile> projectiles;
        
        Joueur joueur;
        

        //! \fn Constructeur
        Game();
        
        //! \fn Destructeur
        ~Game();

        //! \fn Initialiser le jeu
        void init();

        void InitVagueMonstre(); //test Initialisation d'une vague de monstre différent

        void InitPlateauJeu(); //test Initialisation du plateau de jeu, rempli de Def et non Null -> affichage texte

        //! \fn Placer une défense
        //! \param defense défense à placer
        //! \param position position de la défense
        void placerDef(typeDef defense, unsigned int position);

        //! \fn vendre une défense
        //! \param position position de la défense à vendre
        void sellDef(Defense & defense);

        //! \fn Améliorer une défense
        //! \param position position de la défense à améliorer
        void upgradeDef(Defense & defense);

        //! \fn La défense haagrah un monstre
        //! \param IndiceDuMonstre Indice du monstre qui va se faire bully
        //! \param Defposition position de la défense qui va attaquer
        //! \param Defx coord x de la défense à améliorer
        //! \param Defy coord y de la défense à améliorer
        void DefHitMonstre(Monstre & monstre, unsigned int Defposition ,int Defx, int Defy);


};

#endif