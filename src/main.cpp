#include "game.h"
#include <iostream>

int main (void) {

    Game maGame;

    maGame.init();
    maGame.InitPlateauJeu();

    maGame.CasePlateauEstVide();

    
    cout<<endl;
    return 0;
}

//Dcp pour l'instant (prblm makefile) je compile avec g++ -Wall src/main.cpp src/game.cpp src/monstre.cpp src/defense.cpp pour les tests.