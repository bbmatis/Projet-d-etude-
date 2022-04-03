#include "gameTxt.h"
#include <iostream>
#include "game.h"
#include <unistd.h>

using namespace std;

#include <ostream>
namespace Color {
    enum Code {
        FG_RED          = 31,
        FG_GREEN        = 32,
        FG_CYAN         = 36,
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
Color::Modifier green(Color::FG_GREEN);
Color::Modifier cyan(Color::FG_CYAN);



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
            // Si le type de la def est Canon
            else if (game.defenses[indice].getType() == CANON) cout<<red<<" C"<<def;
            // Si le type de la def est Double Canon
            else if (game.defenses[indice].getType() == DOUBLECANON) cout<<red<<"DC"<<def;
            // Si le type de la def est Mortier
            else if (game.defenses[indice].getType() == MORTIER) cout<<red<<" M"<<def;
            cout<<"|";
        }
        cout<<endl;
    }

    // On affiche l'argent du joueur
    cout<<"Argent : "<<game.joueur.money<<endl;
    
}

// Jouer le jeu en mode textuel
void GameTxt::jouer() {


    while(true){

        // On affiche le jeu
        afficher();

        cout<<"votre score est : "<<game.joueur.getScore()<<endl;
        // On demande au joueur de choisir une action
        cout << "Que voulez vous faire ? :\n 1 : Ajouter une défense\n 2 : Améliorer une défense\n "
                "3 : Vendre une défense\n 4 : Lancer la partie\n";
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
             //Test de la fonction d'attaque de la défense

             
            //int def_i = int(position/25);
            //int def_j = position%25;
            int i;
            //TTTTTEEEEEESSSSTTTTT
                /* while(game.monstres[5].getHp() != 0){ //On lance le "niveau" tant que la vague de monstre n'est pas entierement tué

                
                   for(i=0; i<MAX_MONSTRES; ++i){ //pour tout les monstres
                    

                        
                        for(int j = 175; i<=199; i++){

                            game.monstres[i].MoveRight();
                            game.DefHitMonstre(game.monstres[i], j);
                            sleep(1);
                        }
                    }
                    
                } */
                
            
                

                // Je pense faudrait plutôt faire un truc qui boucle sur toutes les défense
                // Et genre chaque défense look si y'a des énemis dans sa zone de défense
                // Si oui on lui fait attaquer
                // Si non on continue
                
                break;
            
            break;
        }




        


    }

}
