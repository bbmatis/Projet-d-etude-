#include "magasin.h"
#include <iostream>

// Acheter une défense
void Magasin::buyDef(typeDef type) {  
    Defense defense(type);
    if (defense.getPrix() <= money) {
        money -= defense.getPrix();
        cout << "Vous avez acheté une " << type << " pour " << defense.getPrix() << " Money" << endl;
    } else {
        cout << "Vous n'avez pas assez d'argent pour acheter cette défense" << endl;
    }

    // TODO: Ajouter la défense au jeu
}

// vendre une défense
void Magasin::sellDef(Defense defense) {
    money += defense.getPrix()/2; // On lui donne que la moitié de la thune hein
    cout << "Vous avez vendu une " << defense.getType() << " pour " << defense.getPrix() << " Money" << endl;

    // TODO: Enlever la défense du jeu
}

// Obtenir l'argent du joueur
unsigned int Magasin::getMoney() const {
    return money;
}

// Modifier l'argent du joueur
void Magasin::setMoney(unsigned int newMoney) {
    money = newMoney;
}

// Améliorer une défense au niveau supérieur
void Magasin::upgradeDef(Defense defense) {
    if (defense.getPrix()*2 <= money) { // TODO : Choisir le cout de l'amélioration
        money -= defense.getPrix();
        defense.upgrade();
        cout << "Vous avez amélioré une " << defense.getType() << " pour " << defense.getPrix() << " Money" << endl;
    } else {
        cout << "Vous n'avez pas assez d'argent pour améliorer cette défense" << endl;
    }
}