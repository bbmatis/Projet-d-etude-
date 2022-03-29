#include "vecteur2D.h"

// Constructeur
Vecteur2D::Vecteur2D()
{
    x,y = 0;
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
Vecteur2D Vecteur2D::operator+(Vecteur2D v)
{
    Vecteur2D res;
    res.x = x + v.x;
    res.y = y + v.y;
    return res;
}

// Operateur -
Vecteur2D Vecteur2D::operator-(Vecteur2D v)
{
    Vecteur2D res;
    res.x = x - v.x;
    res.y = y - v.y;
    return res;
}

// Operateur *
Vecteur2D Vecteur2D::operator*(Vecteur2D v)
{
    Vecteur2D res;
    res.x = x * v.x;
    res.y = y * v.y;
    return res;
}

// Operateur /
Vecteur2D Vecteur2D::operator/(Vecteur2D v)
{
    Vecteur2D res;
    res.x = x / v.x;
    res.y = y / v.y;
    return res;
}