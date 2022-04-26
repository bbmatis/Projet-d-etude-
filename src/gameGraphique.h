#ifndef GAMEGRAPHIQUE_H
#define GAMEGRAPHIQUE_H

#include "game.h"
#include "Menu.h"
#include "Image.h"

#include <SDL2/SDL.h>  
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define DimWindowX 1000
#define DimWindowY 800


// ===== GameGraphique ===== //

class GameGraphique {

    private: 
        Game game;
        Menu menu;
        unsigned int dimx, dimy; //!! Dimentions X et Y de l'image
        SDL_Window * window; //! Fenêtre SDL
        SDL_Renderer * renderer; //! Renderer SDL
        Menu menu;
        
        
        int retour;
        int choix;
        

        Image im_monstre;
        Image im_defenseDOUBLECANON;
        Image im_defenseCANON;
        Image im_defenseMORTIER;
        Image im_defenseRIEN;
        vector<Image>im_defenseRIENTab;
        Image im_hearts;
        Image im_hearts1;
        Image im_hearts2;
        Image im_hearts3;
        Image im_shop;
        Image im_Money;
        Image im_Sell;

    public:
        


        //! \brief Constructeur
        GameGraphique(Game theGame);

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
        void AffichagePateau(); //Iinitialise l'affichage du plateau de def
        void AfficherMenuChoix(); //Affiche le menu pour les choix
        void afficherBoucle();  //! Boucle d'affichage de l'image
        //void afficherDetruit(); //! Déinitialise SDL
        void afficherErreurs();

};

#endif
