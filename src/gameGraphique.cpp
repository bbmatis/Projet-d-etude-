#include "gameGraphique.h"

void GameGraphique::GameGraphique(Game famosoGame) {
    game = famosoGame;
}

void GameGraphique::~GameGraphique {}

void GameGraphique::afficherConsole(){
    int SDL_RenderDrawRect(SDL_Renderer * renderer,const SDL_Rect* rectangle);
}

void GameGraphique::afficherInit() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("GameGraphique", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl; 
        SDL_Quit(); 
        exit(1);
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

}

void Image::afficherBoucle() {
    SDL_Rect rectangle;
    SDL_SetRenderDrawColor(renderer,155,155,155,255);
    SDL_RenderClear(renderer);
    for(unsigned int x=0;x<dimx;x++){
        for(unsigned int y=0;y<dimy;y++){
            Pixel& pix = getPix(x,y);
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
    //unsigned int framesCount = 0;
    afficherInit();

    while(display){
        afficherBoucle();
        //cout<<"Frame n"<<framesCount<<" Zoom x"<<zoom<<endl;
        //framesCount++;

        while (SDL_PollEvent(&events)){
            if (events.type == SDL_QUIT) display = false;
            if (events.type == SDL_KEYDOWN) {
                switch (events.key.keysym.scancode){
                case SDL_SCANCODE_ESCAPE:
                case SDL_SCANCODE_A:
                    display = false;
                    break;
            } 
        }
        SDL_Delay(100);
    }  

    afficherDetruit();
}
