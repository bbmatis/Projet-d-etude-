struct Vecteur2D
{
    
    float x,y;

};

enum TypeMonstres {Mob1, Mob2, Mob3};

class Monstre {

    private:

        
        float speed;            /** \param speed Vitesse du monstre **/
        Vecteur2D position;     /** \param position Vecteur position (x;y) du monstre**/
        unsigned int nb_vie;    /** \param nb_vie Nombre de points de vie du monstre**/
     

    public:
        
        Monstre(TypeMonstres type);     /** \brief Initialise un monstre avec un type donné 
                                            \param type le type du monstre**/
                                        
        Monstre();
        ~Monstre();

        void MoveRight();   /** \brief Fait avancer le monstre de x = speed **/
        void MoveLeft();    /** \brief Fait reculer le monstre de x = speed **/
        void MoveUp();      /** \brief Fait monter le monstre de y = speed **/
        void MoveDown();    /** \brief Fait descendre le monstre de y = speed **/

        unsigned int getLife();     /** \brief Donne la vie du monstre**/
        void removeLife(int nb);    /** \brief Fait décroitre la vie du monstre
                                        \param nb nombre de point de vie à retirer**/

        Vecteur2D getPos();     /** \brief Récupère la position du monstre**/

     

        

};