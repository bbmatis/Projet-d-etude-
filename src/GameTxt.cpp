#include "gameTxt.h"
#include <iostream>

using namespace std;

// Constructeur de GameTxt
GameTxt::GameTxt(Game famosoGame) {
    game = famosoGame;
}

// destructeur de GameTxt
GameTxt::~GameTxt() {}

// Afficher le jeu en mode textuel
void GameTxt::afficher(){ //test voir le .h

    for(int i=0; i<HAUTEUR; i++)
    {
        for(int j=0; j<LARGEUR; j++)
        {
            if(game.defenses[j].getType() == RIEN){ //regarde si la case est "Null"
                cout<<" 0 ";
            }
            else 
                cout<<" 1 ";
        }
        cout<<endl;
    }
    
}