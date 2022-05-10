#ifndef MENU_H
#define MENU_H

#include "Image.h"


#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>

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
        Image font_im2;
        Image font_im3;

        SDL_Color font_color;
        SDL_Color font_color2;
        SDL_Color font_color3;

        SDL_Renderer * renderer; //! Renderer SDL
        SDL_Window * window; //! Fenêtre SDL
        
        std::vector<Scores>scores; //Tableau contenant les les scores

    public : 
        Menu();
        ~Menu();
        void MenuAfficher(); 
        void MenuInit();
        void MenuBoucle();

};

#endif