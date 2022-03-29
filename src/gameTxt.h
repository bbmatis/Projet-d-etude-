#ifndef GAMETXT_H
#define GAMETXT_H

#include "game.h"

class GameTxt {

    private:
        Game game;

    public: 
        //! \fn Constructeur
        //! \param famosoGame Game à partir de la quel on va créer un GameTxt
        GameTxt(Game famosoGame);

        //! \fn Destructeur
        ~GameTxt();

        //! \fn afficher le jeu en mode textuel
        void afficher();

        //! \fn afficher les prix des défenses
        void afficherPrix();
        
};

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 66a5b15db994673f636cc3919132822bca0a6acc
