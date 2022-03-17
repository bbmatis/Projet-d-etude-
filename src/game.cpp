#include "game.h"

Game::Game() {
    monstres = new Monstre [200];
    defenses = new Defense [100];
    plaques = new bool [Largeur*Longueur];
    money = 10;
}

Game::~Game(){
    delete [] monstres;
    delete [] defenses;
    delete [] plaques;
    money = 0; 
}

unsigned char& Game::getPlaque(const unsigned int posX, const unsigned int posY) const {

    
}

void Game::togglePlaque(const bool plaque){

}

void Game::addDefense(const bool plaque, Defense defense){

}

void removeDefense(const bool plaque){

}

Defense& getDefense(const bool plaque){

}
