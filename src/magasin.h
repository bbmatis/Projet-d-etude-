#include "game.h"

class Magasin {

    private:
        unsigned int money; 
        Game game;

    public:
        void acheterDef(); /** \brief permet au joueur d'acheter des défenses **/
        void vendreDef(); /** \brief permet au joueur de vendre des défenses **/
        unsigned int getMoney(); /** \brief lis le nombre d'argent du joueur **/
        unsigned int addMoney(int moula) /** \brief ajoute de l'argent au compteur du joueur **/

};