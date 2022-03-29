#include "game.h"
#include "gameTxt.h"
#include <iostream>

using namespace std;

int main (void) {

    Game maGame;

    maGame.init();
    maGame.InitPlateauJeu();

    // On créer un GameTxt à partir de maGame
    GameTxt maGameTxt(maGame);

    // On affiche le jeu
    maGameTxt.afficher();    


    cout<<endl;
    return 0;
}