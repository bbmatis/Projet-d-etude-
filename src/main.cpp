#include "game.h"
#include "gameTxt.h"
#include "gameGraphique.h"
#include <SDL.h>
#include <iostream>

using namespace std;

int main (void) {
/*
    // Initialisation du jeu
    Game maGame;
    maGame.init();

    // On créer un GameTxt à partir de maGame
    GameTxt maGameTxt(maGame);

    // On lance le jeu
    maGameTxt.jouer();  */

    GameGraphique theGame;
    
    theGame.afficher();

    return EXIT_SUCCESS;
    
}