#include "gameGraphique.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

int  temps () {
    return int(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}


GameGraphique::GameGraphique(Game theGame) {
  game = theGame;
  
}

GameGraphique::~GameGraphique() {
    
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
}


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

    if(TTF_Init() < 0)
    {
        cout <<"Erreur lors de l'initialisation de TTF" <<TTF_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }

    // FONTS
    font = TTF_OpenFont("img/arial.ttf",50);
    if (font == nullptr)
        font = TTF_OpenFont("img/arial.ttf",50);
    if (font == nullptr) {
            cout << "Failed to load img/Arial.ttf SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    game.defenses[186] = Defense(DOUBLECANON); // TEST
    game.defenses[99] = Defense(MORTIER); // TEST 
    game.defenses[254] = Defense(DOUBLECANON); // TEST 
    game.defenses[260] = Defense(CANON); // TEST 
    game.defenses[130] = Defense(DOUBLECANON); // TEST 

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
 
    im_monstre1.loadFromFile("img/Squelette.png", renderer);
    im_monstre2.loadFromFile("img/monstre2.png",renderer);
    im_monstre3.loadFromFile("img/Golem.png", renderer);
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

    

    SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
    SDL_RenderClear(renderer);



    

    // Dessine le plateau de jeu une premiere fois 

    AffichagePateau();

    


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
        else if(game.defenses[j].getType() == DOUBLECANON)
        {
            im_defenseDOUBLECANON.draw(renderer, Defx*37+40, Defy*37+122.5, 35, 35);
        }
        else if(game.defenses[j].getType() == CANON)
        {
            im_defenseCANON.draw(renderer,Defx*37+40, Defy*37+122.5, 35, 35);
        }
        else if(game.defenses[j].getType() == MORTIER)
        {
            im_defenseMORTIER.draw(renderer,Defx*37+40, Defy*37+122.5, 35, 35);
        }
    }

    

    

    for(unsigned int i =0; i<game.monstres.size(); i++)
    {
       
        if(game.monstres[i].getType() == Mob1){
    
            im_monstre1.draw(renderer,game.monstres[i].getPosition().x,game.monstres[i].getPosition().y, 45, 45);
    
        }
        if(game.monstres[i].getType() == Mob2){

            im_monstre2.draw(renderer,game.monstres[i].getPosition().x,game.monstres[i].getPosition().y, 45, 45);
        } 
        if(game.monstres[i].getType() == Mob3){

            im_monstre3.draw(renderer,game.monstres[i].getPosition().x,game.monstres[i].getPosition().y, 45, 45);
        } 
    }

    //affichage de la money
    im_Money.draw(renderer,50, 50, 50, 50);

    ostringstream ss;
    ss<<game.joueur.money;
    string moula(ss.str());

    Couleur_Texte.r = 50; Couleur_Texte.g = 50; Couleur_Texte.b = 255;
    font_im.setSurface(TTF_RenderText_Solid(font,moula.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionJouer;
    positionJouer.x = 170; positionJouer.y = 50; positionJouer.w = 100; positionJouer.h = 50;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionJouer);

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
                                            //Améliorer une défense
}

void GameGraphique::AfficherMessageErreur(int nbErr) {

    string err1 = "Le type de defense n'est pas valide";
    string err2 = "La position choisie est invalide";
    string err3 = "Vous n'avez pas assez d'argent pour acheter cette défense";
    string err = "";

    if(nbErr == -1) {
        err = err1;
    }
    if(nbErr == -2) {
        err = err2;
    }
    if(nbErr == -3) {
        err = err3;
    }

    Couleur_Texte2.r = 250; Couleur_Texte2.g = 50; Couleur_Texte2.b = 55;
    font_im2.setSurface(TTF_RenderText_Solid(font,err.c_str(),Couleur_Texte2));
    font_im2.loadFromCurrentSurface(renderer);

    SDL_Rect positionJouer2;
    positionJouer2.x = 470; positionJouer2.y = 50; positionJouer2.w = 300; positionJouer2.h = 50;
    SDL_RenderCopy(renderer,font_im2.getTexture(),nullptr,&positionJouer2);

}


void GameGraphique::afficherBoucle() {  

    AffichagePateau();
    //AfficherMessageErreur(-2);
}

//Affichage avec le menu de départ 

void GameGraphique::afficher(){

    bool display=true;
    bool lancervague=true;
    bool AfficherMenuChoixBool=false;
    bool clear = false;
    int xMouse, yMouse;

    SDL_Event events;
    afficherInit();

    while(display){
         afficherBoucle();
         touchemonstre = false;

        while(SDL_PollEvent(&events)){

        
            
            if(events.type == SDL_QUIT) display = false;

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
                            
                            AfficherMenuChoixBool = true; //Affiche le menu des choix à effectuer(upgrade, sell, buy)
               
                        }                
                    }
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
                            switch(events.key.keysym.sym){
                            case SDLK_c :
                            
                                retour = game.buyDefense(CANON, i);
                                if (retour == -1) cout<< "Le type de defense n'est pas valide."<<endl;
                                // Si la position est invalide
                                else if (retour == -2) cout << "La position choisie est invalide."<<endl;
                                // Si le joueur n'a pas assez d'argent
                                else if (retour == -3) cout << "Vous n'avez pas assez d'argent pour acheter cette défense."<<endl;
                            
                                break;

                            case SDLK_d :
                            
                                retour = game.buyDefense(DOUBLECANON, i);
                                if (retour == -1) cout<< "Le type de defense n'est pas valide."<<endl;
                                // Si la position est invalide
                                else if (retour == -2) cout << "La position choisie est invalide."<<endl;
                                // Si le joueur n'a pas assez d'argent
                                else if (retour == -3) cout << "Vous n'avez pas assez d'argent pour acheter cette défense."<<endl;
                            
                                break;

                            case SDLK_m :
                            
                                retour = game.buyDefense(MORTIER, i);
                                if (retour == -1) cout<< "Le type de defense n'est pas valide."<<endl;
                                // Si la position est invalide
                                else if (retour == -2) cout << "La position choisie est invalide."<<endl;
                                // Si le joueur n'a pas assez d'argent
                                else if (retour == -3) cout << "Vous n'avez pas assez d'argent pour acheter cette défense."<<endl;
                            break;

                            case SDLK_s : 

                                retour = game.sellDefense(game.defenses[i]);
                                break;

                            default: break;
                            }
                       
                    
                    }
                }
                //Test fonction 
            if(events.key.keysym.sym == SDLK_SPACE)
            {
                SDL_WaitEvent(&events);

                 lancervague = false;
                 //Pour l'instant touche space  mais imaginer un bouton "play" pour lancé la vague de monstre
                SDL_WaitEvent(&events);//permet que l'action ne se realise pas 15 fois en même temps 
                //TODO lancer la vagaue de monstre

            }
            }
            
       
    
        }



        if(lancervague != true){ //Lancer vague

                 // On boucle sur les défenses
                    for (unsigned int i=0; i < game.defenses.size(); i++) {
                        if (game.defenses[i].getType() == RIEN) continue; // Si la case est vide, on passe à la suivante
                        cout<<"Tour de la défense : "<<i<<endl;

                        for (unsigned int a = 0; a < game.monstres.size(); a++) {
                            // Attack de la défense sur monstre a si possible
                            retour = game.DefHitMonstre(game.monstres[a], i, 1);
                            // Si la défense a touché le monstre
                            if (retour == 1) {
                                cout<<"Le monstre #"<<a<<" a été touché par la défense #"<<i<<endl;
                                touchemonstre = true;
                                if(touchemonstre = true) {
                                    //im_monstre1.loadFromFile("img/Golem_Hit.png", renderer);
                                    //im_monstre1.loadFromFile("img/Golem.png", renderer);
                                }
                                
                                
                            }
                            
                        }
                    }

           // On boucle tout les monstres 
                    for (unsigned int i=0; i < game.monstres.size(); i++) {
                        game.monstres[i].MoveRight();
                        
                        // On regarde si le monstre atteint la base du joueur -> decremente nbVie joueur
                        if (game.monstres[i].getPosition().x >= DimWindowX) {
                            // On le supprime si c'est le cas
                            game.monstres.erase(game.monstres.begin()+i);

                            // Et on enlève une vie au joueur
                            game.joueur.setNbVies(game.joueur.getNbVies() - 1);
                        }

                        // On regarde si le monstre n'as plus de vies
                        if (game.monstres[i].getHp() < 1) {
                            // On le supprime si c'est le cas
                            game.monstres.erase(game.monstres.begin()+i);

                            // On ajoute un point au score joueur
                            game.joueur.setScore(game.joueur.getScore() + 1);

                            // On ajoute de l'argent au joueur
                            game.joueur.money += 100;
                            game.nbMonstreTues ++;
                        }

                        // On remet le tableau à la bonne taille
                        game.monstres.shrink_to_fit();
                    }
           
        }
        if(game.monstres.size() == 0) {
            lancervague = true;
            game.vague++;
            game.InitVagueMonstre();    //Recréer une nouvelle vague de monstre
        }


        if(AfficherMenuChoixBool) AfficherMenuChoix();


        SDL_RenderPresent(renderer);
       
       //clear quand on le veut -> garder affiché les choix pour les défenses ?
      
       if(clear != true ) SDL_RenderClear(renderer);
     
  }

}    
