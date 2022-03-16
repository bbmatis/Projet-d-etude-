#include "monstre.h"
#include "defense.h"

#define Largeur 25
#define Longueur 15

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
        unsigned char& getPlaque(const unsigned int posX, const unsigned int posY) const;

        // Inverse l'état d'une plaque
        void togglePlaque(const bool plaque);

        // Ajouter une défense sur le plateau avec le n° de la plaque
        void addDefense(const bool plaque, Defense defense);
        
        // Enlever une défense d'une plaque
        void removeDefense(const bool plaque);

        // Obtenir une defense qui est sur une plaque
        Defense& getDefense(const bool plaque) const;

        // Acheter une defense
        void buyDefense(const unsigned char type);

        // Afficher le jeu en version textuel
        void afficherTextuel() const; 
};