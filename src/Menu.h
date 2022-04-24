#ifndef MENU_H
#define MENU_H

#include "Image.h"


#include <stdlib.h>
#include <iostream>

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include<vector>

#define DimWindowX 1000
#define DimWindowY 800

struct Scores {
    int score;
    char date;
};

class Menu {

    private : 
        
        
        TTF_Font * font;
        Image font_im;
        SDL_Color font_color;
   
        
        std::vector<Scores>scores; //Tableau contenant les les scores

    public : 
    SDL_Renderer * renderer; //! Renderer SDL
    SDL_Window * window; //! Fenêtre SDL
        Menu();
        ~Menu();
        void recupScoreFromFile(); /** \brief récupère le score depuis un fichier externe **/
        void trieScore(); /** \brief trie les scores **/
        void MenuAfficher();
        void MenuInit();
        void MenuBoucle();

};

#endif