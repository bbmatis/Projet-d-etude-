#include "game.h"
#include <iostream>
#include <math.h>
#include <time.h>


using namespace std;

Game::Game() {
    vague = 1;
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
    InitVagueMonstre();
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
    // On met les distances des cases à 404 car on ne sait pas encore quelles défenses sont à quelle distance
    for(int i=0; i<HAUTEUR; i++) for(int j=0; j<LARGEUR; j++) distances[i*LARGEUR+j] = 404;
}

// Acheter et placer une défense
int Game::buyDefense(typeDef defense, unsigned int position) {

    // On vérifie que le type de défense est valide
    if (defense == RIEN) return -1;

    // On vérifie que la position valide et qu'il n'y a pas déjà une défense sur cette position
    if (position > LARGEUR*HAUTEUR || position < 0 || defenses[position].getType() != RIEN) return -2;

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
int Game::DefHitMonstre(Monstre &monstre , unsigned int Defposition, int mode){

    int Defy, Defx;
    if(mode = 0)
    {
        Defy = Defposition/25; //transforme la position en i
        Defx = Defposition%25; //transforme la position en j
    }
    if(mode = 1)
    {
        Defy = (Defposition/25)*37+122 + 17; //transforme la position en i
        Defx = (Defposition%25)*37+40 + 17; //transforme la position en j
    }

    //le monstre est dans le rayon d'attaque de la defense
    if(abs(Distance(monstre.getPosition().x,monstre.getPosition().y, Defx, Defy)) <= defenses[Defposition].getRange()){
        
        //Change la vie du monstre en fonction des dégats de la défense
        monstre.setHp(monstre.getHp()-defenses[Defposition].getDamage());
        return 1;
    }

    return 0;
}

// Tester une case pour savoir si on peut la visiter ou non
int Game::getDistance(unsigned int from, unsigned int to, vector<bool> &visited, vector<int> &toVisit) {
    cout << "getDistance(" << from << "," << to <<")" << endl;

    // On teste si la case est valide
    if (to < 0 || to >= LARGEUR*HAUTEUR) return 403;

    // debug : on affiche si la case est déjà visitée
    // cout << "visited[" << to << "] = " << visited[to] << endl;

    // On teste si la case est visitée
    if (visited[to]) return distances[to];

    // On teste si la case est occupée
    if (defenses[to].getType() != RIEN) return 403;

    // On teste si la case est accessible
    int fromX = from % 25;
    int fromY = from / 25;
    int toX = to % 25;
    int toY = to / 25;

    if (fromX != toX && fromY != toY) return 403;

    // on teste si la case n'est pas déjà dans la liste à visiter
    for (unsigned int i = 0; i < toVisit.size(); i++) {
        if (toVisit[i] == to) return 403;
    }

    // Sinon on retourne true
    return distances[to];
}

// Mettre a jour le tableu des distances des case par rapport a la case de sortie
void Game::updateDistances() {
    int caseDeSortie = 174;
    
    // On initialise un tableau des case déjà visitées
    vector<bool> visited(LARGEUR*HAUTEUR, false);

    // On initialise un tableau des cases a visiter
    vector<int> toVisit;

    // On ajoute la case de sortie à la liste des cases à visiter
    toVisit.push_back(caseDeSortie);

    // On met a 0 la distance de la case de sortie
    distances[caseDeSortie] = 0;

    // On marque la case comme visitée
    visited[caseDeSortie] = true;
    unsigned int compter = 0;
    
    // On parcours les cases à visiter
    while (!toVisit.empty() && compter < 500) {
        compter++;
        // On récupère la case à visiter
        int position = toVisit.back();
        int tmp[4];

        // On retire la case à visiter de la liste
        toVisit.pop_back();

        // On marque la case comme visitée
        visited[position] = true;

        // debug : on affiche la case à visiter
        cout << "Traitement de la case : " << position << " | Dans la pile : "<< toVisit.size()<< endl;

        // On ajoute les cases adjacentes à la case à visiter
        // Dans la liste des cases à visiter si elles sont accessibles
        tmp[0] = getDistance(position, position + 1, visited, toVisit);
        cout << "tmp[0] = " << tmp[0] << endl;
        if (tmp[0] != 403 && tmp[0] == 404) toVisit.push_back(position + 1);
        tmp[1] = getDistance(position, position - 1, visited, toVisit);
        cout << "tmp[1] = " << tmp[1] << endl;
        if (tmp[1] != 403 && tmp[1] == 404) toVisit.push_back(position - 1);
        tmp[2] = getDistance(position, position - LARGEUR, visited, toVisit);
        cout << "tmp[2] = " << tmp[2] << endl;
        if (tmp[2] != 403 && tmp[2] == 404) toVisit.push_back(position - LARGEUR);
        tmp[3] = getDistance(position, position + LARGEUR, visited, toVisit);
        cout << "tmp[3] = " << tmp[3] << endl;
        if (tmp[3] != 403 && tmp[3] == 404) toVisit.push_back(position + LARGEUR);

        // On met à jour la distance de la case
        if (position != caseDeSortie) distances[position] = min(tmp[0], min(tmp[1], min(tmp[2], tmp[3])));
        distances[position]++;

        // debug : afficher le nombre de cases à visiter
        // cout << "Cases à visité : " << toVisit.size()<< endl;
        // cout << "Cases visitées : " << compter << endl;
    
        // debug : affichage des cases à visiter
        // for (unsigned int i = 0; i < toVisit.size(); i++) {
        //     cout << " Case : " <<  toVisit[i] << endl;
        // }

        // on met a jour la distance de la case traitée
        // avec la distance de la case voisine la plus proche de la case de sortie
        // et on ajoute la case à la liste des cases à visiter

    }
    cout << "Nombre de cases visitées : " << compter << endl;
}

