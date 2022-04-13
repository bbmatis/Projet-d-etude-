#ifndef GAMEGRAPHIQUE_H
#define GAMEGRAPHIQUE_H

#include "game.h"
#include "menu.h"
#include <SDL.h>  

class GameGraphique {

    private: 
        Game game;
        unsigned int dimx, dimy; //!! Dimentions X et Y de l'image
        

    public:

        SDL_Window * window;
        SDL_Renderer * renderer;

        std::vector<SDL_Rect> rectangles;
        SDL_Rect rect;
        
        //! \brief Constructeur
        GameGraphique();

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

        void afficherInit(); //! Initialise SDL
        void afficherBoucle();  //! Boucle d'affichage de l'image
        void afficherDetruit(); //! Déinitialise SDL
        void afficherErreurs();

};

#endif
