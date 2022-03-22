class Joueur {

    private:
        unsigned int nb_vies;

    public:
        void removesLifes(); /** \brief diminue le nombre de vies du joueur **/
        unsigned int getLifes(); /** \brief affiche le nombre vies du joueur **/
        unsigned int setLifes(int life); /** \brief modifie le nombre vies du joueur 
                                             \param life vie du joueur **/
}