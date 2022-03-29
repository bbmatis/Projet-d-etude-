#include "gameTxt.h"
#include <iostream>
#include "defense.h"

using namespace std;

#include <ostream>
namespace Color {
    enum Code {
        FG_RED          = 31,
        FG_GREEN        = 32,
        FG_BLUE         = 34,
        FG_MAGENTA      = 35,
        FG_CYAN         = 36,
        BG_RED          = 41,
        BG_GREEN        = 42,
        BG_BLUE         = 44,
        BG_MAGENTA      = 45,
        BG_DEFAULT      = 49,
        FG_DEFAULT      = 39,
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}
Color::Modifier def(Color::FG_DEFAULT);
Color::Modifier bgDef(Color::BG_DEFAULT);
Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier magenta(Color::FG_MAGENTA);
Color::Modifier cyan(Color::FG_CYAN);
Color::Modifier bgRed(Color::BG_RED);
Color::Modifier bgGreen(Color::BG_GREEN);
Color::Modifier bgBlue(Color::BG_BLUE);
Color::Modifier bgMagenta(Color::BG_MAGENTA);



// Constructeur de GameTxt
GameTxt::GameTxt(Game famosoGame) {
    game = famosoGame;
}

// destructeur de GameTxt
GameTxt::~GameTxt() {}

// Afficher le jeu en mode textuel
void GameTxt::afficher(){ //test voir le .h

    for(int i=0; i<HAUTEUR; i++)
    {
        for(int j=0; j<LARGEUR; j++)
        {
            int indice = j+i*LARGEUR;
            cout<<indice;
            if (indice < 100) cout<<" ";
            if (indice < 10) cout<<" ";
            // Si le type de la def est rien a.k.a vide
            if(game.defenses[indice].getType() == RIEN) cout<<" "<<green<<"V"<<def; 
            // Si le type de la def est Double Canon
            else if (game.defenses[indice].getType() == DOUBLECANON) cout<<red<<"DC"<<def;
            // Si le type de la def est Canon
            else if (game.defenses[indice].getType() == CANON) cout<<" C";
            // Si le type de la def est Mortier
            else if (game.defenses[indice].getType() == MORTIER) cout<<" M";
            cout<<"|";
        }
        cout<<endl;
    }

    // On affiche l'argent du joueur
    cout<<"Argent : "<<game.joueur.money<<endl;
    
}

// Jouer le jeu en mode textuel
void GameTxt::jouer() {

    // On affiche le jeu
    afficher();

    // On demande au joueur de choisir une position
    int position;
    cout << "Dans quel case voulez vous placer une defense ?";
    cin >> position;

    // On demande au joueur de choisir un type de defense
    int typeN;
    cout << "Quel type de defense voulez vous placer sur la case "<<position<<"?\n 1 : DOUBLECANNON\n 2 : CANNON\n 3 : MORTIER\n";
    cin >> typeN;

    // On convertit le type de defense en typeDef
    typeDef type;
    if (typeN == 1) type = DOUBLECANON;
    else if (typeN == 2) type = CANON;
    else if (typeN == 3) type = MORTIER;
    else type = RIEN;

    // On demande de placer la defense
    game.placerDef(type, position);

    // On affiche le jeu
    afficher();

}
