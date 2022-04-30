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
        void afficher();

        //! \brief jouer le jeu en mode textuel
        void jouer();
        
};

#endif
