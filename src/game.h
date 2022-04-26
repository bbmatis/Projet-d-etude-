#ifndef GAME_H
#define GAME_H

#include "defense.h"
#include "monstre.h"
#include "joueur.h"
#include "vecteur2D.h"
#include <vector>

#define LARGEUR 25
#define HAUTEUR 15
#define MAX_PROJECTILES 50
#define TAILLE_CASE 4

using namespace std;

// Définition de la stucture Projectile
struct Projectile
{
    unsigned int defenseWhoSendMe;  // Identifie de quelle défense vient le projectile 
    Vecteur2D position;             // Position du projectile
    float vitesse;                  // vitesse du projectile
    
};

class Game {
    private:

        int time; //temps écoulé
        
        //! \brief Retourne la distance entre 2 points
        //! \param x1 position en x du point n°1
        //! \param y1 position en x du point n°1
        //! \param x2 position en y du point n°2
        //! \param y2 position en y du point n°2
        float Distance(int x1, int y1, int x2, int y2);
               
    public:
        std::vector<Monstre> monstres;          // Tableau dynamique de monstres
        std::vector<Defense> defenses;          // Tableau dynamique de défenses
        std::vector<Projectile> projectiles;    // Tableau dynamique de projectiles
        int distances[LARGEUR*HAUTEUR];         // Tableau de distances entre les défenses et les monstress
        unsigned int vague;                     // Indice de vague de monstres 
        unsigned int nbMonstreTues;             // nombre de monstre tué au cours de la partie
        Joueur joueur;
        
        //! \brief Constructeur
        Game();
        
        //! \brief Destructeur
        ~Game();

        //! \brief Initialiser le jeu
        void init();

        //! \brief Initialise des vagues de monstres
        void InitVagueMonstre(); 

        //! \brief Initialisation du plateau de jeu avec des cases vide (plateau de défenses avec type : RIEN)
        void InitPlateauJeu(); 

        //! \brief Permet de placer une défense sur le plateau de jeu.
        //! Retourne 0 si la défense a été placée avec succès, -1 si le type n'est pas valide, -2 si la position n'est pas valide et -3 si le joueur n'a pas assez d'argent.
        //! \param defense défense à placer
        //! \param position position de la défense
        int buyDefense(typeDef defense, unsigned int position);

        //! \brief vendre une défense
        //! \param defense défense à vendre
        int sellDefense(Defense & defense);

        //! \brief Permet d'améliorer une défense.
        //! Retourne le prix d'amélioration si la défense a bien été améliorer, -1 si la position n'est pas valide, l'argent manquant en négatif si le joueur n'a pas assez d'argent.
        //! \param defense défense à améliorer
        int upgradeDefense(Defense & defense);

        //! \brief retroune si le monstre a été haagrah ou non
        //! \param IndiceDuMonstre Indice du monstre qui va se faire bully
        //! \param Defposition position de la défense qui va attaquer
        //! \param Defx coord x de la défense à améliorer
        //! \param Defy coord y de la défense à améliorer
        int DefHitMonstre(Monstre & monstre, unsigned int Defposition);

        //! \brief calcule la distance de chaques case par rapport à la case d'arrivée
        //! Et met à jour le tableau distances
        void updateDistances();

        //! \brief Récupère la distance qui sépare une case de l'arrivée tout en testant si elle est accessible
        //! \param from indice de la case de départ
        //! \param to indice de la case à tester
        //! \param visited tableau de booléens qui indique si une case a déjà été visitée
        //! \param toVisit tableau d'indices de cases à visiter
        //! \return la distance si la case est accessible, 403 sinon (forbidden case)    
        int getDistance(unsigned int from, unsigned int to, vector<bool> & visited, vector<int> & toVisit);

};

#endif