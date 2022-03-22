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
        Monstre * monstres;         // Tableau contenant les monstres
        Defense * defenses;         // Tableau contenant les défenses
        bool * plaques;    // Tableau contenant les case et leur état (0 vide / 1 utilisé par une défense)
        unsigned int money;         // Argent du joueur

    public:
        Game(); // Constructeur
        ~Game(); // Destructeur

        // Obtenir une plaque grâce a des coordonée x / y sur le plateau
        unsigned int& getPlaque(const unsigned int posX, const unsigned int posY) const;
        
        // Enlever une défense d'une plaque
        void removeDefense(const bool plaque);

        // Obtenir une defense qui est sur une plaque
        Defense& getDefense(const bool plaque) const;

        // Acheter une defense
        void buyDefense(const TypeDef type);

        // Afficher le jeu en version textuel
        void afficherTextuel() const; 

        // Afficher le jeu
        void afficherGraphiquement() const;
};