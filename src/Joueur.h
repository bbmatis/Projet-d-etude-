class Joueur {

    private:
        unsigned int nb_vies; /** \param nb_vies la vie du joueur **/

    public:
        void removesLifes(); /** \brief diminue le nombre de vies du joueur **/
        unsigned int getLifes() const ; /** \brief affiche le nombre vies du joueur **/
        unsigned int setLifes(int life); /** \brief modifie le nombre vies du joueur 
                                             \param life vie du joueur modifiée **/
};