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
        //! \return Distance entre 2 points
        float Distance(int x1, int y1, int x2, int y2);
        int modeDAffichage; //mode d'affichage
    public:
        std::vector<Monstre> monstres;          // Tableau dynamique de monstres
        std::vector<Defense> defenses;          // Tableau dynamique de défenses
        std::vector<Projectile> projectiles;    // Tableau dynamique de projectiles
        unsigned int distances[LARGEUR*HAUTEUR];         // Tableau de distances entre les défenses et les monstress
        unsigned int vague;                     // Indice de vague de monstres 
        unsigned int nbMonstreTues;             // nombre de monstre tué au cours de la partie
        Joueur joueur;
        int caseEntree;
        int caseSortie;
        
        //! \brief Constructeur
        Game(unsigned int leModeDAffichage);

        //! \brief Constructeur par défaut
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
        int DefHitMonstre(Monstre & monstre, unsigned int Defposition);

        //! \brief Met à jour les distances des cases par rapport a l'arrivé
        //! \return true si mit a jour avec succès, false sinon
        bool updateDistances();

        //! \brief calcule les distances et retourne un tableau de distances
        //! \return tableau de distances
        unsigned int* getDistances();

        //! \brief Détermine si la case est accessible ou non
        //! \param from position de départ
        //! \param to position d'arrivée
        //! \return true si la case est accessible, false sinon
        bool isAccessibleCase(unsigned int from, unsigned int to);

        //! \brief Récupère la distance qui sépare une case de l'arrivée tout en testant si elle est accessible
        //! \param from indice de la case de départ
        //! \param to indice de la case à tester
        //! \param visited tableau de booléens qui indique si une case a déjà été visitée
        //! \param toVisit tableau d'indices de cases à visiter
        //! \return true si possible et false sinon
        bool canVisitCase(unsigned int from, unsigned int to, vector<bool> & visited, vector<int> & toVisit);

        //! \brief Récupèrer la distance d'une case
        //! \param position la case demander
        //! \return la position de la case (404) si la case n'existe pas
        unsigned int getCaseDistance(unsigned int position, unsigned int tmpDistances[]);

};

#endif