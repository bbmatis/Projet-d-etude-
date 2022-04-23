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

    if(TTF_Init < 0)
    {
        cout <<"Erreur lors de l'initialisation de TTF" <<TTF_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
 
    im_monstre.loadFromFile("img/Golem.png", renderer);
    im_defenseCANON.loadFromFile("img/CANON.png",renderer);
    im_defenseDOUBLECANON.loadFromFile("img/DoubleCanon.png", renderer);
    im_defenseMORTIER.loadFromFile("img/Mortier.png", renderer);
    im_defenseRIEN.loadFromFile("img/dirt.png", renderer);
    im_hearts.loadFromFile("img/Coeur_Complet.png", renderer);
    im_hearts1.loadFromFile("img/Coeur-1.png",renderer);
    im_hearts2.loadFromFile("img/Coeur-2.png",renderer);
    im_hearts3.loadFromFile("img/Coeur-3.png", renderer);
    im_Money.loadFromFile("img/Money.png", renderer);
    im_shop.loadFromFile("img/Shop.png",renderer);
    im_Sell.loadFromFile("img/Sell.png",renderer);

    for(unsigned int i = 0; i<game.monstres.size(); i++) game.monstres[i].setPosition(0, DimWindowY/2);

    SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
    SDL_RenderClear(renderer);

    

    game.defenses[186] = Defense(DOUBLECANON); // TEST
    game.defenses[99] = Defense(DOUBLECANON); // TEST 
    game.defenses[254] = Defense(DOUBLECANON); // TEST 
    game.defenses[260] = Defense(CANON); // TEST 
    game.defenses[130] = Defense(DOUBLECANON); // TEST 

    

    // Dessine le plateau de jeu une premiere fois 

    AffichagePateau();

    


}
void GameGraphique::afficherDetruit() {
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
}

void GameGraphique::AffichagePateau(){

    for(unsigned int j=0; j<game.defenses.size(); j++)
    {
        int Defy = j/25; //transforme la position en i
        int Defx = j%25; //transforme la position en j
        if(game.defenses[j].getType() == RIEN)
        {
            im_defenseRIEN.draw(renderer, Defx*37+40, Defy*37+122.5, 35, 35);
        }
        if(game.defenses[j].getType() == DOUBLECANON)
        {
            im_defenseDOUBLECANON.draw(renderer, Defx*37+40, Defy*37+122.5, 35, 35);
        }
        if(game.defenses[j].getType() == CANON)
        {
            im_defenseCANON.draw(renderer,Defx*37+40, Defy*37+122.5, 35, 35);
        }
        if(game.defenses[j].getType() == MORTIER)
        {
            im_defenseMORTIER.draw(renderer,Defx*37+40, Defy*37+122.5, 35, 35);
        }
    }

    for(unsigned int i =0; i<game.monstres.size(); i++)
    {
        im_monstre.draw(renderer,game.monstres[i].getPosition().x,game.monstres[i].getPosition().y, 45, 45);
    }

    im_Money.draw(renderer,50, 50, 50, 50);
    //TODO Afficher textuel à côté

    // Gère le système d'affichage de vie

    if(game.joueur.getNbVies() == 3) im_hearts.draw(renderer, DimWindowX-200, DimWindowY-100, 180, 60);
    if(game.joueur.getNbVies() == 2) im_hearts1.draw(renderer,DimWindowX-200, DimWindowY-100, 180, 60);
    if(game.joueur.getNbVies() == 1) im_hearts2.draw(renderer,DimWindowX-200, DimWindowY-100, 180, 60);
    if(game.joueur.getNbVies() <  1) im_hearts3.draw(renderer,DimWindowX-200, DimWindowY-100, 180, 60);
    //TODO Faire pour chaques vie du joueur
}

//Affiche le menu pour les choix
void GameGraphique::AfficherMenuChoix(){


    im_shop.draw(renderer,300, 700, 100, 100);//acheter une défense
    im_Sell.draw(renderer,400, 700, 70, 70);//Vendre une défenses
                                            //AMéliorer une défense

} 

void GameGraphique::afficherBoucle() {  

    SDL_RenderClear(renderer);

    AffichagePateau();

 
}





void GameGraphique::afficher(){

    bool display=true;
    int xMouse, yMouse;

    SDL_Event events;
    afficherInit();

    while(display){
         afficherBoucle();

        SDL_WaitEvent(&events);
            
            if (events.type == SDL_QUIT) display = false;

            if(events.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&xMouse, &yMouse);
            }
            if(events.type == SDL_MOUSEBUTTONDOWN)
            {
               
                for(unsigned int i=0; i<game.defenses.size(); i++)
                {
                    int Defy = i/25; //transforme la position en i
                    int Defx = i%25; //transforme la position en j
                    //si on enfonce le bouton gauche de la souris et que la souris se trouve dans l'une des cases 
                    if(xMouse > Defx*37+40 && xMouse < Defx*37+40 + 35 &&  yMouse > Defy*37+122 && yMouse < Defy*37+122 +35)
                    {
                        //cout<<"case :"<<i<<endl;
                       
                        if(events.button.button == SDL_BUTTON_LEFT)
                        {
                  
                            cout<<"Case :"<<i<<" enfoncé"<<endl;
                            
                            AfficherMenuChoix(); //Affiche le menu des choix à effectuer(upgrade, sell, buy)
                                             //Ne s'affiche correctement pas pour l'instant
                         
                        }
                        
            
                        
                    }
                    
                }

                //Pour l'instant bouton souris droit mais imaginer un bouton "play" pour lancé la vague de monstre
                if(events.button.button == SDL_BUTTON_RIGHT)
                {
                 
                    //TODO lancer la vagaue de monstre
                    cout<<"bouton souris droit enfoncé :"<<endl;

                    cout<<game.joueur.getNbVies()<<endl;

                    game.joueur.setNbVies(game.joueur.getNbVies()-1);
                }
                
                
            }

            //TEST Fonction event avec le clavier => si on est dans une case et qu'on appuie sur une des touches ca achète une défense
            if(events.type == SDL_KEYDOWN)
            {
                for(unsigned int i=0; i<game.defenses.size(); i++)
                {
                    int Defy = i/25; //transforme la position en i
                    int Defx = i%25; //transforme la position en j
                    //si on enfonce le bouton gauche de la souris et que la souris se trouve dans l'une des cases 
                    if(xMouse > Defx*37+40 && xMouse < Defx*37+40 + 35 &&  yMouse > Defy*37+122 && yMouse < Defy*37+122 +35)
                    {
                        //cout<<"case :"<<i<<endl;
                       if(game.defenses[i].getType() == RIEN)
                       {

                            if(events.key.keysym.sym == SDLK_c)
                            {
                                game.buyDefense(CANON, i);
                                cout<<"la defense :"<<i<<" à bien été changé en =>" <<game.defenses[i].getType()<<endl; //debug 
                            }
                            if(events.key.keysym.sym == SDLK_d)
                            {
                                game.buyDefense(DOUBLECANON, i);
                                cout<<"la defense :"<<i<<" à bien été changé en =>" <<game.defenses[i].getType()<<endl; //debug 
                            }
                            if(events.key.keysym.sym == SDLK_m)
                            {
                                game.buyDefense(MORTIER, i);
                                cout<<"la defense :"<<i<<" à bien été changé en =>" <<game.defenses[i].getType()<<endl; //debug 
                            }
                       }
                       else cout<<"tu peux pas pd"<<endl;
                       
                        
                    }
                    
                    
                }
                
                
            }
            //Test fonction 
            if(events.key.keysym.sym == SDLK_SPACE)
            {
                //Pour l'instant touche space  mais imaginer un bouton "play" pour lancé la vague de monstre
                SDL_WaitEvent(&events);//permet que l'action ne se realise pas 15 fois en même temps 
                //TODO lancer la vagaue de monstre
                cout<<"touche space droit enfoncé :"<<endl;

                game.monstres[2].MoveRight();

                
                
            }
        

            

        

       
       SDL_RenderPresent(renderer);
     
     
        

  }

    afficherDetruit();
}
