#include "game.h"
#include "defense.h"
#include "monstre.h"

Game::Game() {
    monstres = new Monstre [200];
    defenses = new Defense [100];
    money = 10;
}

Game::~Game(){
    delete [] monstres;
    delete [] defenses;
}