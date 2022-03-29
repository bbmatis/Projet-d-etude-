#include "game.h"
#include <iostream>

using namespace std;

Game::Game() {
    score = .0;
    time = .0f;
    monstres = new Monstre[MAX_MONSTRES];                // Créer un taleau de 200 monstres **/
    defenses = new Defense[LARGEUR*HAUTEUR];    // Créer un tableau de defense de dimension L * H **/
    projectiles = new Projectile[MAX_PROJECTILES]; // Créer un tableau de projectile de dimension L * H **/
}

Game::~Game(){
    delete [] monstres;
    delete [] defenses;
    delete [] projectiles;
    score = 0;
    time = .0f;
}

// Initialiser le jeu
void Game::init() {
    InitPlateauJeu();
    
}

void Game::InitVagueMonstre(){ //test voir le .h

     for(int i=0; i<MAX_MONSTRES/2; i++)
    {
       monstres[i] = Monstre(Mob1);
       monstres[i+MAX_MONSTRES/2] = Monstre(Mob2);
    }
}

// Initialiser le plateau de jeu
void Game::InitPlateauJeu(){

    for(int i=0; i<HAUTEUR; i++) for(int j=0; j<LARGEUR/2; j++)
        defenses[j*2] = Defense(CANNON); // Initialisation des defenses
}

