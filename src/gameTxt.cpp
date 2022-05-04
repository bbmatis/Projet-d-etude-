#include "gameTxt.h"
#include <iostream>
#include "game.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <ostream>

using namespace std;

namespace Color {
    enum Code {
        FG_RED          = 31,
        FG_GREEN        = 32,
        FG_CYAN         = 36,
        BG_RED          = 41,
        BG_DEFAULT      = 49,
        FG_DEFAULT      = 39
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
Color::Modifier bgRed(Color::BG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier cyan(Color::FG_CYAN);



// Constructeur de GameTxt
GameTxt::GameTxt() {
    Game laGame;
    laGame.init();
    game = laGame;
}

// destructeur de GameTxt
GameTxt::~GameTxt() {}

// Afficher le jeu en mode textuel
void GameTxt::afficher(){ //test voir le .h
    int posXMonstre = 0;
    int posYMonstre = 0;
    if (game.monstres.size() > 0){
        // Position des monstres (les monstres ont tous la même position en mode texte)

        posXMonstre = game.monstres[0].getPosition().x;
        posYMonstre = game.monstres[0].getPosition().y;
    }

    for(int i=0; i<HAUTEUR; i++)
    {
        for(int j=0; j<LARGEUR; j++)
        {
            if (posXMonstre == j && posYMonstre == i && game.monstres.size() > 0) cout << bgRed;
            int indice = j+i*LARGEUR;
            cout<<indice;
            if (indice < 100) cout<<" ";
            if (indice < 10) cout<<" ";
            // Si le type de la def est rien a.k.a vide
            if(game.defenses[indice].getType() == RIEN) cout<<" "<<green<<"V"<<def; 
            // Si le type de la def est Canon
            else if (game.defenses[indice].getType() == CANON) cout<<red<<" C"<<def;
            // Si le type de la def est Double Canon
            else if (game.defenses[indice].getType() == DOUBLECANON) cout<<red<<"DC"<<def;
            // Si le type de la def est Mortier
            else if (game.defenses[indice].getType() == MORTIER) cout<<red<<" M"<<def;
            cout<<"|";
            if (posXMonstre == j && posYMonstre == i && game.monstres.size() > 0) cout << bgDef;
        }
        cout<<endl;
    }

    // On affiche l'argent du joueur
    cout<<"Argent : "<<game.joueur.money<<endl;
    cout<<"Monstres en vie : "<<game.monstres.size()<<endl;
    cout<<"Score : "<<game.joueur.getScore()<<endl;
    cout<<"Vague : "<<game.vague<<endl;
    cout<<"NbVie : "<<red<<game.joueur.getNbVies()<<def<<endl;
    
    // On affiche un tableau avec les distances des cases par rapport a la sortie
    // for(int i=0; i<HAUTEUR; i++) {
    //     for(int j=0; j<LARGEUR; j++) {
    //         int indice = j+i*LARGEUR;
    //         if (game.distances[indice] < 100) cout<<" ";
    //         if (game.distances[indice] < 10) cout<<" ";
    //         // On affiche la distance de la case par rapport a la sortie
    //         cout<<game.distances[indice]<<"|";
    //     }
    //     cout<<endl;
    // }
    
}

// Jouer le jeu en mode textuel
void GameTxt::jouer() {
    srand(time(NULL));
    clock_t t_time;

    // On affiche le jeu plateau de jeu
    afficher();

    // Tant que le joueur a des vies
    while(game.joueur.getNbVies() > 0){ 
    
        cout<<"====================================="<<endl;
        cout<<"Vague en approche : Vague N°"<<game.vague<<" ( "<<game.vague*4<<" monstres)"<<endl;


        // On demande au joueur de choisir une action
        cout << "Que voulez vous faire ? :\n 1 : Ajouter une défense\n 2 : Améliorer une défense\n "
                "3 : Vendre une défense\n 4 : Jouer le prochain tour\n";
        int choix;
        cin >> choix;

        // On déclare une variable pour stocker les retours des fonctions
        int retour;

        // On fait l'action correspondante au choix du joueur
        switch(choix)
        {
            case 1 :
                // On demande au joueur de choisir une position
                int position;
                cout << "Dans quel case voulez vous placer une defense ? ";
                cin >> position;

                // On demande au joueur de choisir un type de defense
                int typeN;
                cout << "Quel type de defense voulez vous placer sur la case "<<position<<"?\n 1 : CANON (50)\n 2 : DOUBLECANON (100)\n 3 : MORTIER (200)\n";
                cin >> typeN;

                // On convertit le type de defense en typeDef
                typeDef type;
                if (typeN == 1) type = CANON;
                else if (typeN == 2) type = DOUBLECANON;
                else if (typeN == 3) type = MORTIER;
                else type = RIEN;

                // On demande a game de placer la defense
                retour = game.buyDefense(type, position);

                // On regarde si c'est un succès
                if (retour == 0) cout <<green<< "Vous avez bien placé une defense dans la case "<<position<<" !\n"<<def;
                else {
                    // Sinon c'est qu'il y as une erreur
                    cout << red << "Erreur : ";
                    // Si le type de defense est invalide
                    if (retour == -1) cout<< "Le type de defense n'est pas valide."<<endl;
                    // Si la position est invalide
                    else if (retour == -2) cout << "La position choisie est invalide."<<endl;
                    // Si le joueur n'a pas assez d'argent
                    else if (retour == -3) cout << "Vous n'avez pas assez d'argent pour acheter cette défense."<<endl;
                    // Si la défense bloque le passage
                    else if (retour == -4) cout << "Vous ne pouvez pas poser de défensses ici cela bloquerait le passage pour les ennemies."<<endl;
                    // Si l'erreur n'est pas connue (seems weird :thonk:)
                    else cout << "Erreur inconnue."<<endl; 
                    cout << def;
                }

                break;

            case 2 :
                // On demande au joueur de choisir une position
                cout << "Donner la position de la défense à améliorer : ";
                cin >> position;

                //Upgrade la défense qui est à la position n°_
                retour = game.upgradeDefense(game.defenses[position]);

                // On regarde si c'est un succès
                if (retour > 0) cout << green << "Vous avez bien amélioré la défense de la case "<<position<<" et cela vous as couté "<<retour<<" d'argent !\n"<<def;
                else {
                    // Sinon c'est qu'il y as une erreur
                    cout << red << "Erreur : ";
                    // Si la position est invalide
                    if (retour == -1) cout << "La position choisie est invalide."<<endl;
                    // Si la défense n'est pas à la position
                    else cout << "Vous n'avez pas l'argent pour améliorer cette défense. (il vous manque "<<-retour<<" d'argent)"<<endl;
                    cout << def;
                }
                break;
            
            case 3 : 

                cout<< "Donner la position de la défense à vendre : ";
                cin>>position;

                //Vend la défense qui est à la position n°_
                retour = game.sellDefense(game.defenses[position]);

                // Si la vente est un succès
                if (retour > 0) cout<<green<<"La défense a été vendue avec succés ! Vous avez récupérer " << retour << " d'argent !"<<def<<endl;
                else cout<<red<<"Erreur : Il n'y as pas de défense à cette position."<<def<<endl;

                break;

            case 4 :

                // on fait jouer les tour
                bool vagueEnCours = true;
                while(vagueEnCours){   
                    vagueEnCours = game.playTurn();

                    afficher(); //réaffiche le plateau pour voir les monstres avancer
                    this_thread::sleep_for(chrono::milliseconds(500)); //met le jeu en pause pdt 0.5 seconde pour mieux voir 
                }
            
                break;
                
        }
        afficher(); // afficher le plateau de jeu

        cout<<endl;
    }

    cout<<red<<"Vous n'avez plus de vie, la partie est terminé"<<def<<endl;
    
    cout<<"Votre score est de : "<<game.joueur.getScore()<<endl;
    cout<<"Vous avez tué : "<<game.nbMonstreTues<<endl;

}
