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

        //! \brief opération d'addition avec un autre vecteur
        //! \param other_v vecteur n°2
        Vecteur2D operator+(Vecteur2D other_v);

        //! \brief opération de soustraction avec un autre vecteur
        //! \param other_v vecteur n°2
        Vecteur2D operator-(Vecteur2D other_v);

        //! \brief opération de multiplication avec un autre vecteur
        //! \param other_v vecteur n°2
        Vecteur2D operator*(Vecteur2D other_v);

        //! \brief opération de division avec un autre vecteur
        //! \param other_v vecteur n°2
        Vecteur2D operator/(Vecteur2D other_v);
};

#endif