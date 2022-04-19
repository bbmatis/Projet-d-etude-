#include "gameGraphique.h"
#include <iostream>

GameGraphique::GameGraphique() {}

GameGraphique::~GameGraphique() {}

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
    SDL_SetRenderDrawColor(renderer,155,155,155,255);
    SDL_RenderClear(renderer);
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
        while (SDL_PollEvent(&events)){
            if (events.type == SDL_QUIT) display = false;
        }
    }

    afficherDetruit();
}
