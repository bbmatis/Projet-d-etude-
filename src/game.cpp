#include "game.h"
#include <iostream>

 
Game::Game() {
    score = .0;
    time = .0f;
    monstres = new Monstre[200];                /** \brief Créer un taleau de 200 monstres **/
    defenses = new Defense[LARGEUR*HAUTEUR];    /** \brief Créer un tableau de defense de dimension L * H **/
}

Game::~Game(){
    delete [] monstres;
    delete [] defenses;
    score = .0;
    time = .0f;
}

void Game::DefineMonstres(){ /** \brief Défini les vagues de monstres avec types différents **/
    for(int i =0; i<100; i++)
    {
        
        monstres[i] = Monstre(Mob1);
    
    }
     for(int i =100; i<200; i++)
    {
        
        monstres[i] = Monstre(Mob2);
    
    }
}


