#include "Menu.h"

using namespace std;

Menu::~Menu(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
}

Menu::Menu(){}

void Menu::MenuInit(){

   
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() < 0) {
        cout << "Erreur lors de l'initialisation de SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

        // Creation de la fenetre
    window = SDL_CreateWindow("Marine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // FONTS
    font = TTF_OpenFont("img/arial.ttf",50);
    if (font == nullptr)
        font = TTF_OpenFont("img/arial.ttf",50);
    if (font == nullptr) {
            cout << "Failed to load img/Arial.ttf SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    //Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

}

void Menu::MenuAfficher(){

    font_color2.r = 50;font_color2.g = 250;font_color2.b = 255;
    font_im2.setSurface(TTF_RenderText_Solid(font,"Options",font_color2));
	font_im2.loadFromCurrentSurface(renderer);
    // options
    SDL_Rect position2;
    position2.x = 270; position2.y = 249; position2.w = 100; position2.h = 30;
    SDL_RenderCopy(renderer,font_im2.getTexture(),nullptr,&position2); 

    font_color3.r = 50;font_color3.g = 250;font_color3.b = 255;
    font_im3.setSurface(TTF_RenderText_Solid(font,"Options",font_color3));
	font_im3.loadFromCurrentSurface(renderer);
    // options
    SDL_Rect position3;
    position3.x = 270; position3.y = 249; position3.w = 100; position3.h = 30;
    SDL_RenderCopy(renderer,font_im2.getTexture(),nullptr,&position3);

}

void Menu::MenuBoucle(){
    bool display=true;
    int xMouse, yMouse;

    SDL_Event events;

    MenuInit();

    while(display){

        SDL_WaitEvent(&events);
            
            if (events.type == SDL_QUIT) display = false;

            if(events.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&xMouse,&yMouse);
                if(xMouse > 270 && yMouse > 49 && xMouse < 370 && yMouse < 79) {
                    //lancer le jeu quand on appuie sur jouer
                }
            }
            if(events.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&xMouse,&yMouse);
                if(xMouse > 270 && yMouse > 249 && xMouse < 370 && yMouse < 279) {
                    //ouvre le menu d'options 
                }
            }
        MenuAfficher();
        SDL_RenderPresent(renderer);

        //clear quand on le veut -> garder affiché les choix pour les défenses ?
        bool clear = true;
        if(clear != true ) SDL_RenderClear(renderer);
    }
     
} 





