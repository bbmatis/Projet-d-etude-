#include "game.h"
#include "gameTxt.h"
#include "gameGraphique.h"
#include <SDL.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {

    // Initialisation du jeu
    Game maGame;
    maGame.init();

    // On regarde si un argument est passé en paramètre
    // Si oui et si c'est -t ou --txt, on lance le jeu en mode texte
    // Sinon, on lance le jeu en mode graphique

    if (argc == 2 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--txt") == 0)) {
        // On créer un GameTxt à partir de maGame
        GameTxt maGameTxt(maGame);

        // Et on lance le jeu en mode texte
        maGameTxt.jouer(); 
    } else {
        GameGraphique theGame;
        theGame.afficher();
    } 

    return 0;
}