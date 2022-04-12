#ifndef GAMEGRAPHIQUE_H
#define GAMEGRAPHIQUE_H

#include "game.h"
#include "menu.h"
#include <SDL2.h/SDL.h>  

class GameGraphique {

    private: 
        Game game;
        unsigned int dimx, dimy; //!! Dimentions X et Y de l'image
        SDL_Window * window; //! Fenêtre SDL
        SDL_Renderer * renderer //! Renderer SDL
        void afficherInit() //! Initialise SDL
        void afficherBoucle();  //! Boucle d'affichage de l'image
        void afficherDetruit(); //! Déinitialise SDL

    public:
        //! \brief Constructeur
        GameGraphique(Game famosoGame);

        //! \brief Destructeur
        ~GameGraphique();

        /*! \brief Obtient la dimention X de l'image
         */
        unsigned int getDimX();
        
        /*! \brief Obtient la dimention Y de l'image
         */
        unsigned int getDimY();

        //! \brief afficher le jeu en mode graphique
        void afficherGame();

        //! \brief afficher les prix des défenses
        void afficherPrix();

        //! \brief Afficher l'image de la console
        void afficherConsole();

        //! \brief Afficher l'image dans une fenêtre SDL2
        void afficher();

};

#endif
