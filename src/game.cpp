#include "game.h"
#include <iostream>
 
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
    // TODO

}

