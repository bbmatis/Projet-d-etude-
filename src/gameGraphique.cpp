#include "gameGraphique.h"
#include <iostream>

GameGraphique::GameGraphique() {}

GameGraphique::~GameGraphique() {}

void GameGraphique::afficherConsole(){
    
}

void GameGraphique::afficherInit() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("Marine versus the Arabs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_Rect rect;

    for(int i = 0; i<15; i++)
    {
      for(int j=0; j<25; j++){
        
        rectangles.push_back(rect);
  
      }
    }


}
void GameGraphique::afficherDetruit() {
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    std::vector<SDL_Rect>().swap(rectangles);
    SDL_Quit();
}


void GameGraphique::afficherBoucle() {  

    
    SDL_SetRenderDrawColor(renderer, 0, 15, 155, 255);
    SDL_RenderClear(renderer);

    
  

    for(int i = 0; i<15; i++)
    {
      for(int j=0; j<25; j++){
        SDL_SetRenderDrawColor(renderer,i*j*5+50,i*j*5,i*j*2, 155);
        rectangles[j+i*25].h = 35;
        rectangles[j+i*25].w = 35;
        rectangles[j+i*25].x = j*37+40;
        rectangles[j+i*25].y = i*37+122.5; 

        SDL_RenderFillRect(renderer, &rectangles[j+i*25]);
      }
    }


    SDL_RenderPresent(renderer);


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
