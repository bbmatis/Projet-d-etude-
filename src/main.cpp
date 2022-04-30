#include "game.h"
#include "gameTxt.h"
#include "gameGraphique.h"
#include <SDL.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {

    // On regarde si un argument est passé en paramètre
    // Si oui et si c'est -t ou --txt, on lance le jeu en mode texte
    // Sinon, on lance le jeu en mode graphique

    if (argc == 2 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--txt") == 0)) {
        // On créer une partie en Txt
        GameTxt maGameTxt;

        // Et on lance le jeu en mode texte
        maGameTxt.jouer(); 
    } else {
        // On créer une partie en Graphique
        GameGraphique GameGraphique;

        // Et on lance le jeu en mode graphique
        GameGraphique.afficher();
    } 

    return EXIT_SUCCESS;
    
}