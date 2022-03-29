#include "game.h"
#include "menu.h"

class GameGraphique {

    private: 
        Game game;

    public:
        //! \fn Constructeur
        GameGraphique();

        //! \fn Destructeur
        ~GameGraphique();

        //! \fn afficher le jeu en mode graphique
        void afficherGame();

        //! \fn afficher les prix des défenses
        void afficherPrix();

};
