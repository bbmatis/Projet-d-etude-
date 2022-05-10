#include "game.h"
#include <iostream>
#include <fstream> // <-- Pour lire et écrire dans le fichier "Score.txt"
#include <string> // <-- Pour pouvoir déclarer les variable "string"
#include <math.h>
#include <time.h>
#include <cassert>


using namespace std;

Game::Game(unsigned int leModeDAffichage) {
    vague = 1;
    nbMonstreTues = 0;
    modeDAffichage = leModeDAffichage;
}

Game::Game() {
    vague = 1;
    nbMonstreTues = 0;
    modeDAffichage = 0;
}

Game::~Game(){
    vector<Monstre>().swap(monstres);       //remplace le tableau de monstres par un tableau null
    vector<Defense>().swap(defenses);
    vector<Projectile>().swap(projectiles);
}

// Initialiser le jeu
void Game::init() {
    vague = 1;
    InitPlateauJeu();   // Initialise le plateau de jeu
    InitVagueMonstre();

    defenses[186] = Defense(DOUBLECANON); // TEST

    updateDistances();
}

//Initialise le tableau de monstre (vague)
void Game::InitVagueMonstre(){ 
    // monstres.push_back(Monstre(Mob1));
    // monstres[0].firstMove(1, 1);
    // return;
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
        monstres[i].initMonstre(i, modeDAffichage, vague);
    }
}

// Initialiser le plateau de jeu (défenses)
void Game::InitPlateauJeu(){
    // On créer les cases vides
    for(int i=0; i<HAUTEUR; i++) for(int j=0; j<LARGEUR; j++) defenses.push_back(Defense());
    // On met les distances des cases à 404 car on ne sait pas encore quelles défenses sont à quelle distance
    for(int i=0; i<HAUTEUR; i++) for(int j=0; j<LARGEUR; j++) distances[i*LARGEUR+j] = 404;
}

void Game::recupScoreFromFile() {
    
} 

void Game::enregistreScore() {
    unsigned int score[2];
    score[0] = joueur.getScore();
    score[1] = 18;
    const int length = 10;
    string joueur[2];
    joueur[0] = "Player"; // <-- Tes variables "string" (chaîne de caractères) contenant les pseudos
    joueur[1] = "Test";
    //string Texte[2]; // <-- Création d'un tableau comportant un certain nombre de valeurs

    /* int Prenoms = 0;
    int Nbr = 0; */

    string const NomFichier = "test.txt"; //Chemin d'accès au fichier
    ofstream ScoreEcriture(NomFichier.c_str()); //Ouverture du fichier en mode "écriture"
    if (ScoreEcriture) {
        for(int i=0;i<2;i++) {
            ScoreEcriture << joueur[i] << endl;
            for(int j=0;j<2;j++) {
                ScoreEcriture << score[j] << endl;
            }
        }
    }

    /*ifstream lectureScore("test.txt");  //Ouverture du fichier en mode "lecture"

    if(lectureScore)
    {
        string ligne;
    
        while (getline(lectureScore, ligne))
        {  
            if (ligne == joueur1)
            {
                Prenoms = 1;
            }
            if(ligne == joueur2)
            {
                Prenoms = 2;
            }

            Nbr = Nbr + 1;
            Texte[Nbr] = ligne;

        //}
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier!" << endl;
    }
 
    ofstream ScoreEcriture(NomFichier.c_str()); //Ouverture du fichier en mode "écriture"

    if (ScoreEcriture)
    {
        if (Prenoms == 1)
        {
            for (int i = 1; i <= Nbr; ++i)
            {
                ScoreEcriture << Texte[i] << endl;
            }
            ScoreEcriture << score << " ";
            }
            else
            { 
                for (int i = 1; i <= Nbr; ++i)
                {
                    ScoreEcriture << Texte[i];

                    if (Nbr >= 1)
                    {
                        ScoreEcriture << endl;
                    }
                }
                ScoreEcriture << joueur1 << endl << score << " ";
            //}
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier!" << endl;
    }*/
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
    // On met a joour les distances
    updateDistances();
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
    int MonstreX = monstre.getPosition().x;
    int MonstreY = monstre.getPosition().y;
    int tailleCase = 1;
    if(modeDAffichage == 1)
    {
        tailleCase = 37;
        // Adapte la position de la défense au mode graphique
        Defy = Defy*tailleCase+122+17;
        Defx = Defx*tailleCase+40+17;
        // Adapte la position du monstre au mode graphique
        MonstreY = MonstreY+122+17;
        MonstreX = MonstreX+40+17;
    } 

    //le monstre est dans le rayon d'attaque de la defense
    // Distance entre le monstre et la défense

    float distance = Distance(MonstreX, MonstreY, Defx, Defy);

    if(distance <= defenses[Defposition].getRange()*tailleCase){        
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
bool Game::canVisitCase(int from, int to, vector<bool> &visited, vector<int> &toVisit) {
    // On vérifie que la case est bien accessible
    assert(isAccessibleCase(from, to));    

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
    if (tmpDistances[175] == 404) return false;
    for (unsigned int i = 0; i < LARGEUR*HAUTEUR; i++) distances[i] = tmpDistances[i];
    return true;
}


// Joue un tour de jeu
bool Game::playTurn() {
    int tailleCase = 1;
    int largeurMax = LARGEUR;
    int facteurFrames = 1;
    if (modeDAffichage == 1) {
        tailleCase = 37;
        largeurMax = 920;
        facteurFrames = 100;
    }
    for(unsigned int i=0; i<monstres.size(); i++){
        Vecteur2D monstrePos = monstres[i].getPosition();

        // Centre de la case ou est le monstre
        float centreCaseX = monstrePos.x + tailleCase/2;
        float centreCaseY = monstrePos.y + tailleCase/2;

        // On calcule la position du monstre en case
        int X = floor((centreCaseX)/tailleCase);
        int Y = floor((centreCaseY)/tailleCase);
        const unsigned int monstreCase = Y*LARGEUR + X;

        // On fait déplacer le monstre vers sa cible si il ne l'as pas atteinte on continue
        if (!monstres[i].moveToTargetPosition()) {
            continue;
        }

        // On regarde si le monstre a la case de sortie et si oui il sort du plateau
        if (monstreCase == caseSortie) {
            monstres[i].setTargetPosition(5000, monstrePos.y);
            continue;
        }
        

        int tmpCase = -1;
        // On regarde si la case du haut est accessible
        if (isAccessibleCase(monstreCase, monstreCase - LARGEUR)) {
            tmpCase = monstreCase - LARGEUR;
        }
        // On regarde si la case de droite est accessible
        if (isAccessibleCase(monstreCase, monstreCase + 1)) {
            // On regarde si elle est plus proche

            if (tmpCase == -1) {
                tmpCase = monstreCase + 1;
            } else if (distances[monstreCase + 1] < distances[tmpCase]) {
                tmpCase = monstreCase + 1;
            }
        }
        // On regarde si la case du bas est accessible
        if (isAccessibleCase(monstreCase, monstreCase + LARGEUR)) {
            // On regarde si elle est plus proche
            if (tmpCase == -1) {
                tmpCase = monstreCase + LARGEUR;
            }else if (distances[monstreCase + LARGEUR] < distances[tmpCase]) {
                tmpCase = monstreCase + LARGEUR;
            }
        }
        // On regarde si la case de gauche est accessible
        if (isAccessibleCase(monstreCase, monstreCase - 1)) {
            // On regarde si elle est plus proche
            if (tmpCase == -1) {
                tmpCase = monstreCase - 1;
            }else if (distances[monstreCase - 1] < distances[tmpCase]) {
                tmpCase = monstreCase - 1;
            }
        }

        // On défini la nouvel target du monstre
        int targetX = (tmpCase % LARGEUR)*tailleCase;
        int targetY = (tmpCase / LARGEUR)*tailleCase;
        monstres[i].setTargetPosition(targetX, targetY);
    }

    // On boucle sur les défenses
    for (unsigned int i=0; i < defenses.size(); i++) {

        // Si la case est vide, on passe à la suivante
        if (defenses[i].getType() == RIEN) continue; 
        
        // On regarde quels sont les monstre que la défense peut attaquer
        for (unsigned int a = 0; a < monstres.size(); a++) {                    
            // On regarde si le monstre a encore de la vie
            if (monstres[a].getHp() >= 0) {
                if (defenses[i].getLastHit() + defenses[i].getReloadTime()*facteurFrames < frameCount ) {
                    int retour = DefHitMonstre(monstres[a], i);
                    // Si la défense a touché le monstre ont met a jour le temps de reload
                    if (retour == 1) defenses[i].setLastHit(frameCount);
                }
            }
        }
    }

    // On boucle sur les monstre
    for (unsigned int a = 0; a < monstres.size(); a++) {
        // On regarde si le monstre a encore de la vie
        if (monstres[a].getHp() <= 0) {
            // On le supprime si c'est le cas
            monstres.erase(monstres.begin()+a);
            // Et ajoute le score suivant le type de monstre
            int score = 0;
            switch (monstres[a].getType()) {
                case Mob1:
                    score += 10;
                    break;
                case Mob2:
                    score += 20;
                    break;
                case Mob3:
                    score += 30;
                    break;
            }
            
            // on ajoute le score
            joueur.setScore(joueur.getScore() + score);
            nbMonstreTues++;
            joueur.money += score;
        }

        // On regarde si le monstre atteint la base du joueur -> decremente nbVie joueur
        if (monstres[a].getPosition().x >= largeurMax) {
            // On le supprime si c'est le cas
            monstres.erase(monstres.begin()+a);
            // Et on enlève une vie au joueur
            joueur.setNbVies(joueur.getNbVies() - 1);
        }
    }

    // On remet a niveau la taille du tableau monstres
    monstres.shrink_to_fit();

    frameCount++;
    if(monstres.size() == 0) {
        vague++;
        InitVagueMonstre();    //Recréer une nouvelle vague de monstre
        return false;
    }

    return true;
} 

// Game over
bool Game::isGameOver() {
    if (joueur.getNbVies() <= 0) return true;
    return false;
}