#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur {

    private:
        unsigned int nbVies;

    public:
        //! \fn Constructeur
        Joueur();

        //! \fn Destructeur
        ~Joueur();

        //! \fn Obtenir le nombre de vies du joueur
        unsigned int getNbVies() const;

        //! \fn Modifier le nombre de vies du joueur
        //! \param newNbVies Nouveau nombre de vies
        void setNbVies(unsigned int newNbVies);

};

#endif

