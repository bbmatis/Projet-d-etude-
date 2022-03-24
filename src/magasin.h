#include "game.h"

class Magasin {

    private:
        unsigned int money; /** \param money porte-monnaie du joueur pendant la partie **/

    public:
        void acheterDef(typeDef type); /** \brief permet au joueur d'acheter des défenses 
                                           \param type le type de la defense acheter **/
        void vendreDef(typeDef type); /** \brief permet au joueur de vendre des défenses
                                          \param type le type de la defense acheter **/
        unsigned int getMoney() const; /** \brief lis le nombre d'argent du joueur **/
        unsigned int addMoney(Monstre type); /** \brief ajoute de l'argent au compteur du joueur 
                                                 \param type le type du Monstre tuer **/

};