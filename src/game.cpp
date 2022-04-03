#include "game.h"
#include <iostream>
#include <math.h>
#include <time.h>


using namespace std;

Game::Game() {
    vague = 0;
    nbMonstreTues = 0;
}

Game::~Game(){
    vector<Monstre>().swap(monstres);       //remplace le tableau de monstres par un tableau null
    vector<Defense>().swap(defenses);
    vector<Projectile>().swap(projectiles);
}

// Initialiser le jeu
void Game::init() {
    InitPlateauJeu();   // Initialise le plateau de jeu
}

//Initialise le tableau de monstre (vague)
void Game::InitVagueMonstre(){ 
    for(unsigned int i=0; i<vague*4; i++) {
        //  Obtenir un monstre aléatoire pour définir la raretée du monstre
        int monstreRarity = rand() % 100;

        if (monstreRarity <= 20 && vague > 4) {         //20% de chance de spawn un mob3 à partir de la vague 6
            monstres.push_back(Monstre(Mob3));
        } else if (monstreRarity <= 50 && vague > 2) {  //50% de chance de spawn un mob2 à partir de la vague 4
            monstres.push_back(Monstre(Mob2));
        } else {
            monstres.push_back(Monstre(Mob1));
        }
    }
}

// Initialiser le plateau de jeu (défenses)
void Game::InitPlateauJeu(){
    // On créer les cases vides
    for(int i=0; i<HAUTEUR; i++) for(int j=0; j<LARGEUR; j++) defenses.push_back(Defense());
}

// Acheter et placer une défense
int Game::buyDefense(typeDef defense, unsigned int position) {

    // On vérifie que le type de défense est valide
    if (defense == RIEN) return -1;

    // On vérifie que la position valide et qu'il n'y a pas déjà une défense sur cette position
    if (position > LARGEUR*HAUTEUR || position <= 0 || defenses[position].getType() != RIEN) return -2;

    // On créer la défense pour obtenir son prix
    Defense defense_tmp(defense);

    // On vérifie que le joueur à assez d'argent pour acheter la défense
    if (defense_tmp.getPrix() > joueur.money) return -3;

    // Tout est ok, on ajoute la défense au plateau de jeu
    defenses[position] = defense_tmp;
    joueur.money -= defense_tmp.getPrix();
    
    // On retourne 0 pour indiquer que la défense a été placée
    return 0;
}

// vendre une défense 
int Game::sellDefense(Defense & defense) {

    // Si la défense est vide
    if (defense.getType() == RIEN) return -1;

    // On définit le prix de la vente de la défense
    int prix = defense.getPrix()*defense.getLevel() / 2;

    // On vend la défense
    joueur.money += prix; // On lui donne que la moitié de la thune hein
    defense = Defense(); //remplace la def par une case vide
    return prix;
}

// Améliorer une défense au niveau supérieur
int Game::upgradeDefense(Defense &defense) {
    // On défini le prix de l'amélioration
    unsigned int prix = defense.getPrix() * 2;
    // Si il n'y a pas de défense sur la case
    if (defense.getType() == RIEN) return -1;
    // Si le joueur n'as pas assez d'argent on retourne l'argent manquant en négatif
    else if (prix > joueur.money) return joueur.money - prix;

    // Sinon on lui enlève l'argent et on améliore la défense et on retourne le prix de l'amélioration
    joueur.money -= defense.getPrix()*2;
    defense.upgrade();
    return defense.getPrix();
}

//retourne la distance entre 2 points
float Game::Distance(int x1, int y1, int x2, int y2)
{
    int xDist = x2 - x1;
    int yDist = y2 - y1;

    return sqrt(pow(xDist, 2) + pow(yDist, 2));
}

//La défense attaque le monstre
int Game::DefHitMonstre(Monstre &monstre , unsigned int Defposition){

    
    int Defy = Defposition/25; //transforme la position en i
    int Defx = Defposition%25; //transforme la position en j

    //le monstre est dans le rayon d'attaque de la defense
    if(abs(Distance(monstre.getPosition().x,monstre.getPosition().y, Defx, Defy)) <= defenses[Defposition].getRange()){
        
        //Change la vie du monstre en fonction des dégats de la défense
        monstre.setHp(monstre.getHp()-defenses[Defposition].getDamage());
        return 1;
    }

    return 0;
}



