#ifndef GAMEGRAPHIQUE_H
#define GAMEGRAPHIQUE_H

#include "game.h"
#include "menu.h"
#include <SDL2/SDL.h>  
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define DimWindowX 1000
#define DimWindowY 800


class Image {

private:

    SDL_Surface * m_surface;
    SDL_Texture * m_texture;
    bool m_hasChanged;

public:
    Image () ;
    ~Image();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};



class GameGraphique {

    private: 
        Game game;
        unsigned int dimx, dimy; //!! Dimentions X et Y de l'image
        SDL_Window * window; //! Fenêtre SDL
        SDL_Renderer * renderer; //! Renderer SDL
        std::vector<SDL_Rect> rectangles;
        SDL_Rect rect;  
        

        Image im_monstre;
        Image im_defenseDC;
        Image im_defenseRI;

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
        void afficherBoucle();  //! Boucle d'affichage de l'image
        void afficherDetruit(); //! Déinitialise SDL
        void afficherErreurs();

};

#endif
