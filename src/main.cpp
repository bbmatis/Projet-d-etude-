#include "game.h"
#include "gameTxt.h"
#include "gameGraphique.h"
#include <SDL2.h/SDL.h>
#include <iostream>

using namespace std;

int main (void) {
/*
    // Initialisation du jeu
    Game maGame;
    maGame.init();

    // On créer un GameTxt à partir de maGame
    GameTxt maGameTxt(maGame);

    // On lance le jeu
    maGameTxt.jouer();  */

    Game theGame;

    SDL_Event events;
    bool isOpen{ true };

    while(isOpen) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Choisir la couleur noir  
        SDL_RenderClear(renderer); // Colorier en noir toutes la fenêtre 

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Choisir la couleur blanche 

        SDL_RenderPresent(renderer);
    }
      

    return 0;
}