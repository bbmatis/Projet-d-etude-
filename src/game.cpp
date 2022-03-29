#include "game.h"
#include <iostream>

using namespace std;

Game::Game() {
    score = .0;
    time = .0f;
    monstres = new Monstre[MAX_MONSTRES];           // Créer un taleau de 200 monstres **/
    defenses = new Defense[LARGEUR*HAUTEUR];        // Créer un tableau de defense de dimension L * H **/
    projectiles = new Projectile[MAX_PROJECTILES];  // Créer un tableau de projectile de dimension L * H **/
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
    InitPlateauJeu();
    
}

void Game::InitVagueMonstre(){ //test voir le .h
    // TODO : Initialiser les monstres de la vague

}

// Initialiser le plateau de jeu
void Game::InitPlateauJeu(){
    // TODO : Initialiser le plateau de jeu

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

// Placer une défense
void Game::placerDef(typeDef defense, unsigned int position) {
    // On vérifie que le type de défense est valide
    if (defense == RIEN) {
        cout << "Type de défense non valide" << endl;
        return;
    }

    // On vérifie que la position valide
    if (position > LARGEUR*HAUTEUR || position <= 0) {
        cout << "La position " << position << " n'est pas valide" << endl;
        return;
    }

    // On vérifie que la position est libre
    if (defenses[position].getType() != RIEN) {
        cout << "La position " << position << " est déjà occupée" << endl;
        return;
    }

    // On créer la défense
    Defense defense_tmp(defense);

    // On vérifie que le joueur a assez d'argent
    if (defense_tmp.getPrix() > joueur.money) {
        cout << "Vous n'avez pas assez d'argent pour acheter cette défense" << endl;
        return;
    }

    // On ajoute la défense au jeu
    defenses[position] = defense_tmp;
    joueur.money -= defense_tmp.getPrix();
    cout << "Vous avez acheté une " << defense_tmp.getType() << " pour " << defense_tmp.getPrix() << " Money" << endl;
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

