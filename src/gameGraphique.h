#include "game.h"
#include "menu.h"

class GameGraphique {

    private: 
        Game game;

    public:
        //! \brief Constructeur
        GameGraphique();

        //! \brief Destructeur
        ~GameGraphique();

        //! \brief afficher le jeu en mode graphique
        void afficherGame();

        //! \brief afficher les prix des défenses
        void afficherPrix();

};
