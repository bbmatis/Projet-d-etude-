#ifndef GAMETXT_H
#define GAMETXT_H

#include "game.h"

class GameTxt {

    private:
        Game game;

    public: 
        //! \brief Constructeur
        //! \param famosoGame Game à partir de la quel on va créer un GameTxt
        GameTxt();

        //! \brief Destructeur
        ~GameTxt();

        //! \brief afficher le jeu en mode textuel
        void afficherPlateau();

        //! \brief jouer le jeu en mode textuel
        void jouer();

        //! \brief afficher un tour de jeu en mode textuel
        void afficherTour();

        //! \brief afficher le menu en mode textuel
        void afficherMenu();

        //! \brief afficher le menu de fin de partie en mode textuel
        void afficherFin();
        
};

#endif
