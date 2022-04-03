#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur {

    private:
        int nbVies;             // nombre de vie du joueur
        unsigned int score;     // score du joueur

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
        unsigned int getScore() const;

        //! \brief Modifier le score du joueur
        //! \param newScore Nouveau score
        void setScore(unsigned int newScore);

};

#endif

