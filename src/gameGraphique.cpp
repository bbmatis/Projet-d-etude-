#include "gameGraphique.h"
#include <iostream>

GameGraphique::GameGraphique() {
}

GameGraphique::~GameGraphique() {}

void GameGraphique::afficherConsole(){
    int SDL_RenderDrawRect(SDL_Renderer * renderer,const SDL_Rect* rectangle);
}

void GameGraphique::afficherInit() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("GameGraphique", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl; 
        SDL_Quit(); 
        exit(1);
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

}

void GameGraphique::afficherBoucle() {
    SDL_Rect rectangle;
    SDL_SetRenderDrawColor(renderer,155,155,155,255);
    SDL_RenderClear(renderer);
    for(unsigned int x=0;x<dimx;x++){
        for(unsigned int y=0;y<dimy;y++){
            SDL_RenderFillRects(renderer,&rectangle,1);
        }
    }

    SDL_RenderPresent(renderer);
}

void GameGraphique::afficherDetruit() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void GameGraphique::afficher(){
    bool display=true;
    SDL_Event events;
    afficherInit();

    while(display){
        afficherBoucle();
        SDL_Renderer * renderer;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Choisir la couleur noir  
        SDL_RenderClear(renderer); // Colorier en noir toutes la fenêtre 
    }

    afficherDetruit();
  }
