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
Vecteur2D::~Vecteur2D(){}