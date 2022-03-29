#include "game.h"
#include <iostream>

using namespace std;

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

void Game::InitVagueMonstre(){ //test voir le .h

     for(int i=0; i<MAX_MONSTRES/2; i++)
    {
       monstres[i] = Monstre(Mob1);
       monstres[i+MAX_MONSTRES/2] = Monstre(Mob2);
    }
}

void Game::InitPlateauJeu(){ //test voir le .h

    for(int i=0; i<HAUTEUR; i++)
    {
        for(int j=0; j<LARGEUR/2; j++)
        {
            defenses[j*2] = Defense(CANNON); 
        }
    }
}

// Acheter une défense
void Game::buyDef(typeDef type) {  
    Defense defense(type);
    if (defense.getPrix() <= joueur.money) {
         joueur.money -= defense.getPrix();
        cout << "Vous avez acheté une " << type << " pour " << defense.getPrix() << " Money" << endl;
    } else {
        cout << "Vous n'avez pas assez d'argent pour acheter cette défense" << endl;
    }

    // TODO: Ajouter la défense au jeu
}

// vendre une défense
void Game::sellDef(Defense defense) {
    joueur.money += defense.getPrix()/2; // On lui donne que la moitié de la thune hein
    cout << "Vous avez vendu une " << defense.getType() << " pour " << defense.getPrix() << " Money" << endl;

    // TODO: Enlever la défense du jeu
}

// Améliorer une défense au niveau supérieur
void Game::upgradeDef(Defense defense) {
    if (defense.getPrix()*2 <= joueur.money) { // TODO : Choisir le cout de l'amélioration
        joueur.money -= defense.getPrix();
        defense.upgrade();
        cout << "Vous avez amélioré une " << defense.getType() << " pour " << defense.getPrix() << " Money" << endl;
    } else {
        cout << "Vous n'avez pas assez d'argent pour améliorer cette défense" << endl;
    }
}

