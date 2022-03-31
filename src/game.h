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
        //! \brief Permet de placer une défense sur le plateau de jeu.
        //! Retourne 0 si la défense a été placée avec succès, -1 si le type n'est pas valide, -2 si la position n'est pas valide et -3 si le joueur n'a pas assez d'argent.
        //! \param defense défense à placer
        //! \param position position de la défense
        int buyDefense(typeDef defense, unsigned int position);

        //! \fn vendre une défense
        //! \param position position de la défense à vendre
        int sellDefense(Defense & defense);

        //! \fn Améliorer une défense
        //! \brief Permet d'améliorer une défense.
        //! Retourne le prix d'amélioration si la défense a bien été améliorer, -1 si la position n'est pas valide, l'argent manquant en négatif si le joueur n'a pas assez d'argent.
        //! \param position position de la défense à améliorer
        int upgradeDefense(Defense & defense);

        //! \fn La défense haagrah un monstre
        //! \param IndiceDuMonstre Indice du monstre qui va se faire bully
        //! \param Defposition position de la défense qui va attaquer
        //! \param Defx coord x de la défense à améliorer
        //! \param Defy coord y de la défense à améliorer
        void DefHitMonstre(Monstre & monstre, unsigned int Defposition ,int Defx, int Defy);


};

#endif