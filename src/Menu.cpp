#include "Menu.h"

using namespace std;



Menu::~Menu(){}

void Menu::recupScoreFromFile(){} /** \brief récupère le score depuis un fichier externe **/

void Menu::trieScore(){} /** \brief trie les scores **/

Menu::Menu(){}

void Menu::MenuInit(){

   
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
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

	font_color.r = 80;font_color.g = 50;font_color.b = 255;
	font_jouer.setSurface(TTF_RenderText_Solid(font,"Jouer",font_color));
	font_jouer.loadFromCurrentSurface(renderer);

    font_color.r = 50;font_color.g = 250;font_color.b = 255;
    font_options.setSurface(TTF_RenderText_Solid(font,"Options",font_color));
	font_options.loadFromCurrentSurface(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

}

void Menu::MenuAfficher(){

    // Ecrire un titre par dessus
    SDL_Rect positionJouer;
    positionJouer.x = 270; positionJouer.y = 49; positionJouer.w = 100; positionJouer.h = 30;
    SDL_RenderCopy(renderer,font_jouer.getTexture(),nullptr,&positionJouer);

    // options
    SDL_Rect positionOptions;
    positionOptions.x = 270; positionOptions.y = 249; positionOptions.w = 100; positionOptions.h = 30;
    SDL_RenderCopy(renderer,font_options.getTexture(),nullptr,&positionOptions); 

}

void Menu::MenuBoucle(){
    bool display=true;
    int xMouse, yMouse;

    SDL_Event events;

    MenuInit();

    while(display){

        SDL_WaitEvent(&events);
            
            if (events.type == SDL_QUIT) display = false;

                    
        MenuAfficher();
        SDL_RenderPresent(renderer);

        //clear quand on le veut -> garder affiché les choix pour les défenses ?
        bool clear = true;
        if(clear != true ) SDL_RenderClear(renderer);
    }
     
  }





