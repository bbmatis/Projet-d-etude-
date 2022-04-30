#include "game.h"
#include <iostream>
#include <math.h>
#include <time.h>


using namespace std;

Game::Game(unsigned int leModeDAffichage) {
    vague = 1;
    nbMonstreTues = 0;
    caseEntree = 175;
    caseSortie = 199;
    modeDAffichage = leModeDAffichage;
}

Game::Game() {
    vague = 1;
    nbMonstreTues = 0;
    caseEntree = 175;
    caseSortie = 199;
    modeDAffichage = 0;
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
        // Faire le premier mouvement du monstre
        monstres[i].firstMove(i);
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
    if (defense == RIEN || position == caseEntree || position == caseSortie) return -1;

    // On vérifie que la position valide et qu'il n'y a pas déjà une défense sur cette position
    if (position > LARGEUR*HAUTEUR || position < 0 || defenses[position].getType() != RIEN) return -2;

    // On créer la défense pour obtenir son prix
    Defense defense_tmp(defense);

    // On vérifie que le joueur à assez d'argent pour acheter la défense
    if (defense_tmp.getPrix() > joueur.money) return -3;

    // Tout semble bon on met la défense sur la case en gardant l'ancienne au cas ou
    Defense base = defenses[position];
    defenses[position] = defense_tmp;
    // On essaye de mettre a jour les distances pour voir si la case est valide
    if (!updateDistances()) {
        // Si la case n'est pas valide on remet l'ancienne défense
        defenses[position] = base;
        return -4;
    }
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

    int Defy, Defx;
    if(modeDAffichage == 0)
    {
        Defy = Defposition/25; //transforme la position en i
        Defx = Defposition%25; //transforme la position en j
    }
    else if(modeDAffichage == 1)
    {
        Defy = (Defposition/25)*37+122+18; //transforme la position en i
        Defx = (Defposition%25)*37+40+18; //transforme la position en j
    } 

    //le monstre est dans le rayon d'attaque de la defense
    // Distance entre le monstre et la défense

    float distance = Distance(monstre.getPosition().x, monstre.getPosition().y, Defx, Defy);
    if(distance <= defenses[Defposition].getRange()){
        cout << "Le monstre est dans le rayon d'attaque de la défense" << endl;
        cout << "Distance : " << distance << endl;
        cout << "Rayon : " << defenses[Defposition].getRange() << endl;
        // On affiche position du monstre et position de la défense
        cout << "Monstre : " << monstre.getPosition().x << " " << monstre.getPosition().y << endl;
        cout << "Defense : " << Defx << " " << Defy << endl;
        
        //Change la vie du monstre en fonction des dégats de la défense
        monstre.setHp(monstre.getHp()-defenses[Defposition].getDamage());
        return 1;
    }

    return 0;
}

// Détermine si une casse est accessible depuis une position donnée
bool Game::isAccessibleCase(unsigned int from, unsigned int to) {
   // On teste si la case est valide
    if (to < 0 || to >= LARGEUR*HAUTEUR) return false;
    if (from < 0 || from >= LARGEUR*HAUTEUR) return false;

    // On vérifie si la case est accessible de là d'ou on vient
    int fromX = from % LARGEUR;
    int fromY = from / LARGEUR;
    int toX = to % LARGEUR;
    int toY = to / LARGEUR;

    if (abs(fromX - toX) > 1 || abs(fromY - toY) > 1) return false;

    return true;
}

// Tester une case pour savoir si on peut la visiter ou non
bool Game::canVisitCase(unsigned int from, unsigned int to, vector<bool> &visited, vector<int> &toVisit) {
    // cout << "getDistance(" << from << "," << to <<")" << endl;

    // On teste si la case est visitée
    if (visited[to]) return false;

    // On teste si la case est occupée
    if (defenses[to].getType() != RIEN) return false;

    // on teste si la case n'est pas déjà dans la liste à visiter
    for (unsigned int i = 0; i < toVisit.size(); i++) if (toVisit[i] == to) return false;

    // Sinon on retourne true
    return true;
}

// récupère la distance d'une case
unsigned int Game::getCaseDistance(unsigned int position, unsigned int tmpDistances[]) {
    if (position < 0 || position > LARGEUR*HAUTEUR) return 404;
    return tmpDistances[position];
}


// Mettre a jour le tableu des distances des case par rapport a la case de sortie
unsigned int * Game::getDistances() {
    static unsigned int tmpDistances[LARGEUR*HAUTEUR];
    for (unsigned int i = 0; i < LARGEUR*HAUTEUR; i++) tmpDistances[i] = 404;

    int caseDeSortie = caseSortie;
    
    // On initialise un tableau des case déjà visitées
    vector<bool> visited(LARGEUR*HAUTEUR, false);

    // On initialise un tableau des cases a visiter
    vector<int> toVisit;

    // On ajoute la case de sortie à la liste des cases à visiter
    toVisit.push_back(caseDeSortie);

    // On met à 0 la distance de la case de sortie
    tmpDistances[caseDeSortie] = 0;

    // On marque la case comme visitée
    visited[caseDeSortie] = true;
    unsigned int compter = 0;
    
    // On parcours les cases à visiter le compter < 400 c'est au casou un bug
    while (!toVisit.empty() && compter < 400) {
        // On récupère l'élément en bas de pile 
        int position = toVisit.front();
        int tmp[4] = {404, 404, 404, 404};

        // On retire l'élément en bas de pile
        toVisit.erase(toVisit.begin());

        // On marque la case comme visitée
        visited[position] = true;

        // On regarde les cases adjacentes
        if (isAccessibleCase(position, position - 1)) { // On regarde la case à gauche
            tmp[0] = getCaseDistance(position - 1, tmpDistances);
            if (canVisitCase(position, position - 1, visited, toVisit)) toVisit.push_back(position - 1);
        }
        
        if (isAccessibleCase(position, position + 1)) { // On regarde la case a droite
            tmp[1] = getCaseDistance(position + 1, tmpDistances);
            if (canVisitCase(position, position + 1, visited, toVisit)) toVisit.push_back(position + 1);
        }

        if (isAccessibleCase(position, position - LARGEUR)) { // On regarde la case en haut
            tmp[2] = getCaseDistance(position - LARGEUR, tmpDistances);
            if (canVisitCase(position, position - LARGEUR, visited, toVisit)) toVisit.push_back(position - LARGEUR);
        }

        if (isAccessibleCase(position, position + LARGEUR)) { // On regarde la case en bas
            tmp[3] = getCaseDistance(position + LARGEUR, tmpDistances);
            if (canVisitCase(position, position + LARGEUR, visited, toVisit)) toVisit.push_back(position + LARGEUR);
        }

        // On met à jour la distance de la case avec la distance de la case la plus proche
        if (position != caseDeSortie) tmpDistances[position] = min(tmp[0], min(tmp[1], min(tmp[2], tmp[3])));
        tmpDistances[position]++; // Du coup on l'incrémente de 1
        compter++; // On incrémente le compteur de sécurité
    }
    return tmpDistances;
}

// Mettre a jour les distances

bool Game::updateDistances() {
    unsigned int *tmpDistances = getDistances();
    if (tmpDistances[175] == 404) {
        cout << "L'arrivée est inaccessible" << endl;
        return false;
    }
    for (unsigned int i = 0; i < LARGEUR*HAUTEUR; i++) distances[i] = tmpDistances[i];
    return true;
}

