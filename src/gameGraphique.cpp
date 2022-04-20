#include "gameGraphique.h"
#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

int  temps () {
    return int(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}


Image::Image () : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false) {
}

Image::~Image()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}


void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr) {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr) {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (m_texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);
    if (m_texture == nullptr) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?m_surface->w:w;
    r.h = (h<0)?m_surface->h:h;

    if (m_hasChanged) {
        ok = SDL_UpdateTexture(m_texture,nullptr,m_surface->pixels,m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(renderer,m_texture,nullptr,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return m_texture;}

void Image::setSurface(SDL_Surface * surf) {m_surface = surf;}












// =============== Class GameGraphique ================= /

GameGraphique::GameGraphique(Game theGame) {
  game = theGame;
}

GameGraphique::~GameGraphique() {}

void GameGraphique::afficherConsole(){
    
}

void GameGraphique::afficherInit() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("Marine versus the Arabs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

    im_monstre.loadFromFile("Golem.png", renderer);
    im_defense.loadFromFile("dirt.png", renderer);
    for(int i = 0; i<game.monstres.size(); i++) game.monstres[i].setPosition(0, 400);

    


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


    game.defenses[186] = Defense(CANON); // TEST 

    for(int j=0; j<game.defenses.size(); j++)
    {
        int Defy = j/25; //transforme la position en i
        int Defx = j%25; //transforme la position en j
        if(game.defenses[j].getType() == RIEN)
        {
            im_defense.draw(renderer, Defx*37+40, Defy*37+122.5, 35, 35);
        }
        if(game.defenses[j].getType() == CANON)
        {
            im_monstre.draw(renderer, Defx*37+40, Defy*37+122.5, 35, 35);
        }
    }

    for(int i = 0; i<4; i++)
    {

        if(game.monstres[i].getPosition().x == DimWindowX){
            game.monstres[i].setPosition(0, 400);
        }

        im_monstre.draw(renderer,game.monstres[i].getPosition().x,game.monstres[i].getPosition().y, 45, 45);
        game.monstres[i].MoveRight();
        game.monstres[i%2].MoveUp(); //debug pour voir si il s'affiche bien plusieurs monstres 
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
