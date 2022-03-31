#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur {

    private:
        unsigned int nbVies;
        unsigned int score;

    public:

        unsigned int money; /** \param money porte-monnaie du joueur pendant la partie **/

        //! \fn Constructeur
        Joueur();

        //! \fn Destructeur
        ~Joueur();
        
        //! \fn Obtenir le nombre de vies du joueur
        unsigned int getNbVies() const;

        //! \fn Modifier le nombre de vies du joueur
        //! \param newNbVies Nouveau nombre de vies
        void setNbVies(unsigned int newNbVies);

        //! \fn Obtenir le score du joueur
        unsigned int getScore() const;

        //! \fn Modifier le score du joueur
        //! \param newScore Nouveau score
        void setScore(unsigned int newScore);

};

#endif

