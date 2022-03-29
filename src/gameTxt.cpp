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
            // Si e type de la def est rien a.k.a vide
            if(game.defenses[j].getType() == RIEN) cout<<" V";
            else if (game.defenses[j].getType() == DOUBLECANNON) cout<<" D";
            else if (game.defenses[j].getType() == CANNON) cout<<" C";
            else if (game.defenses[j].getType() == MORTIER) cout<<" M";
            cout<<":"<<j+i*LARGEUR;
        }
        cout<<endl;
    }
    
}
