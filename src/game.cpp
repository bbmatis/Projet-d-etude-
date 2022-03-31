#include "game.h"
#include <iostream>
#include <math.h>

using namespace std;

Game::Game() {
    score = .0;
    time = .0f;
}

Game::~Game(){
    vector<Monstre>().swap(monstres);
    vector<Defense>().swap(defenses);
    vector<Projectile>().swap(projectiles);
    score = 0;
    time = .0f;
}

// Initialiser le jeu
void Game::init() {
    InitPlateauJeu();
    InitVagueMonstre();
    
}

//retourne la distance entre 2 points
float Game::Distance(int x1, int y1, int x2, int y2)
{
    int xDist = x2 -x1;
    int yDist = y2 - y1;

    return sqrt(pow(xDist, 2) + pow(yDist, 2));
}

//Initialise le tableau de monstre (vague)
void Game::InitVagueMonstre(){ 

     for(int i=0; i<MAX_MONSTRES/2; i++)
    {
       monstres.push_back(Monstre(Mob1));
       
    }
    for(int i=MAX_MONSTRES/2; i<MAX_MONSTRES; i++)
    {
       monstres.push_back(Monstre(Mob2));
       
    }
}

// Initialiser le plateau de jeu (défenses)
void Game::InitPlateauJeu(){

    for(int i=0; i<HAUTEUR; i++){

        for(int j=0; j<LARGEUR; j++) 
        {
            defenses.push_back(Defense());

        }
    
    }
}

// Placer une défense
int Game::placerDefense(typeDef defense, unsigned int position) {

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
void Game::sellDef(Defense & defense) {

    if(defense.getType() != RIEN) 
    {
        joueur.money += defense.getPrix()/2; // On lui donne que la moitié de la thune hein
        cout << "Vous avez vendu une " << defense.getType() << " pour " << defense.getPrix()/2 << " Money" << endl;
        defense = Defense(); //remplace la def par une case vide
    }
    else{
        cout<<"Impossible : La case ne contient aucune défense !\n";
    }



}

// Améliorer une défense au niveau supérieur
void Game::upgradeDef(Defense &defense) {
    if (defense.getType() == RIEN){

        cout<<"Il n'y a pas de défense sur cette case !"<<endl;
    }
    else if (defense.getPrix()*2 <= joueur.money) { // TODO : Choisir le cout de l'amélioration
        joueur.money -= defense.getPrix();
        defense.upgrade();
        cout << "Vous avez amélioré une " << defense.getType() << " pour " << defense.getPrix() << " Money" << endl;
    } 
    else {
        cout << "Vous n'avez pas assez d'argent pour améliorer cette défense" << endl;
    }
}

//La défense attaque le monstre
void Game::DefHitMonstre(Monstre &monstre , unsigned int Defposition, int Defx, int Defy){

    //le monstre est dans le rayon d'attaque de la defense
    if(Distance(monstre.getPosition().x,monstre.getPosition().y, Defx, Defy) < 3)
    {
        
        //Charge la nouvelle vie du monstre en fonction de l'atq de la def 
        int new_life = monstre.getHp()-defenses[Defposition].getDamage();
      
        //Change la vie du monstre
        monstre.setHp(new_life);

        cout<<"le monstre à été touché, il lui reste : "<<monstre.getHp()<<" hp"<<endl;
        
    }
    //le monstre est en dehors du rayon d'attaque de la defense
    else
        cout<<"le monstre n'a pas été touché"<<endl;

}

