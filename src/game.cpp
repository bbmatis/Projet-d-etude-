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

// récupérer le score
unsigned int Game::getScore() {
    return score;
}

// définir le score
void Game::setScore(unsigned int new_score) {
    score = new_score;
}

void Game::InitVagueMonstre(){

     for(int i=0; i<MAX_MONSTRES/2; i++)
    {
       monstres[i] = Monstre(Mob1);
       monstres[i+MAX_MONSTRES/2] = Monstre(Mob2);
    }
}

void Game::InitPlateauJeu(){

    for(int i=0; i<HAUTEUR; i++)
    {
        for(int j=0; j<LARGEUR/2; j++)
        {
            defenses[j] = Defense(RIEN);
            defenses[j*2] = Defense(CANNON); 
        }
    }
}

void Game::CasePlateauEstVide(){

    for(int i=0; i<HAUTEUR; i++)
    {
        for(int j=0; j<LARGEUR; j++)
        {
            if(defenses[j].getType() == RIEN){
                cout<<" * ";
            }
            else 
                cout<<" - ";
        }
        cout<<endl;
    }
    
}

