#include "game.h"

class Magasin {

    private:
        unsigned int money; 

    public:
        void acheterDef(typeDef type); /** \brief permet au joueur d'acheter des défenses **/
        void vendreDef(typeDef type); /** \brief permet au joueur de vendre des défenses **/
        unsigned int getMoney(); /** \brief lis le nombre d'argent du joueur **/
        unsigned int addMoney(Monstre type); /** \brief ajoute de l'argent au compteur du joueur **/

};