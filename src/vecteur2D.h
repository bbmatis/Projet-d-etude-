#ifndef VECTEUR_H
#define VECTEUR_H

class Vecteur2D
{
    public:
        float x,y;

        //! \brief constructeur
        Vecteur2D(); 

        //! \brief constructeur avec paramètres
        //! \param x coordonée x
        //! \param y coordonée y
        Vecteur2D(float x, float y);

        //! \brief destructeur
        ~Vecteur2D();
};

#endif