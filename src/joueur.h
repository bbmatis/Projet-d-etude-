#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>

using namespace std;

class Joueur {

    private:
        int nbVies;             // nombre de vie du joueur
        int score;     // score du joueur
        string nom = "NIC";  // nom du joueur

    public:

        unsigned int money; // porte-monnaie du joueur pendant la partie

        //! \brief Constructeur
        Joueur();

        //! \brief Destructeur
        ~Joueur();
        
        //! \brief Obtenir le nombre de vies du joueur
        int getNbVies() const;

        //! \brief Modifier le nombre de vies du joueur
        //! \param newNbVies Nouveau nombre de vies
        void setNbVies(int newNbVies);

        //! \brief Obtenir le score du joueur
        int getScore() const;

        //! \brief Modifier le score du joueur
        //! \param newScore Nouveau score
        void setScore(unsigned int newScore);

        //! \brief Obtenir le nom du joueur
        string getNom() const;

        //! \brief Modifier le nom du joueur
        //! \param newNom Nouveau nom
        void setNom(string newNom);

        //! \brief Remet a 0 le joeuur
        void reset();
};

#endif

