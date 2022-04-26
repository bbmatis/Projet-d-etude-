#include "vecteur2D.h"
#include <iostream>

// Constructeur
Vecteur2D::Vecteur2D()
{
    x = 0;
    y = 0;
}

// Constructeur avec parametres
Vecteur2D::Vecteur2D(float nX, float nY)
{
    x = nX;
    y = nY;
}

// Destructeur
Vecteur2D::~Vecteur2D()
{
}

// Operateur +
Vecteur2D Vecteur2D::operator+(Vecteur2D other_v)
{
    Vecteur2D res;
    res.x = x + other_v.x;
    res.y = y + other_v.y;
    return res;
}

// Operateur -
Vecteur2D Vecteur2D::operator-(Vecteur2D other_v)
{
    Vecteur2D res;
    res.x = x - other_v.x;
    res.y = y - other_v.y;
    return res;
}

// Operateur *
Vecteur2D Vecteur2D::operator*(Vecteur2D other_v)
{
    Vecteur2D res;
    res.x = x * other_v.x;
    res.y = y * other_v.y;
    return res;
}

// Operateur /
Vecteur2D Vecteur2D::operator/(Vecteur2D other_v)
{
    Vecteur2D res;
    if(other_v.x != 0 && other_v.y != 0)
    {
        res.x = x / other_v.x;
        res.y = y / other_v.y;
        
    }
    else 
        std::cout<<"impossible d'avoir une valeur null au dénominateur"<<std::endl;

    return res;
        
}