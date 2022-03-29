#ifndef VECTEUR_H
#define VECTEUR_H

class Vecteur2D
{
    public:
        float x,y;
        Vecteur2D();
        Vecteur2D(float x, float y);
        ~Vecteur2D();
        Vecteur2D operator+(Vecteur2D v);
        Vecteur2D operator-(Vecteur2D v);
        Vecteur2D operator*(Vecteur2D v);
        Vecteur2D operator/(Vecteur2D v);
};

#endif