#include "game.h"

class GameTxt {

    private:
        Game game;

    public: 
        //! \fn Constructeur
        GameTxt();

        //! \fn Destructeur
        ~GameTxt();

        //! \fn afficher le jeu en mode textuel
        void afficherGame();

        //! \fn afficher les prix des défenses
        void afficherPrix();
        
};