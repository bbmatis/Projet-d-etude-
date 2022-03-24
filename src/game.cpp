#include "game.h"
#include <iostream>

Game::Game() {
    monstres = new Monstre [200];
    defenses = new Defense [LARGEUR*HAUTEUR];
}

Game::~Game(){
    delete [] monstres;
    delete [] defenses;
}

void Game::DefineMonstres(){

    Vecteur2D PosInit;
    PosInit.x, PosInit.y =50;
    for(int i=0; i<100; ++i)
    {
        monstres[i] = Monstre(Mob1, PosInit);
    }
}
