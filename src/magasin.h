#include "game.h"

class Magasin {

    private:
        unsigned int money; /** \param money porte-monnaie du joueur pendant la partie **/

    public:
        //! \fn Constructeur
        Magasin();

        //! \fn Destructeur
        ~Magasin();

        //! \fn Acheter une défense
        //! \param type type de défense à acheter
        void buyDef(typeDef type);

        //! \fn vendre une défense
        //! \param defense défense à vendre
        void sellDef(Defense defense);

        //! \fn Améliorer une défense
        //! \param defense défense à améliorer
        void upgradeDef(Defense defense);

        //! \fn Obtenir l'argent du joueur
        unsigned int getMoney() const;
        
        //! \fn Modifier l'argent du joueur
        void setMoney(unsigned int newMoney);
        

};