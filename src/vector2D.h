class Vecteur2D
{
    
    Vecteur2D x,y;

};

Vecteur2D::Vecteur2D() {
    x = 0;
    y = 0;
}

Vecteur2D::~Vecteur2D() {}

Vecteur2D::operator+(Vecteur2D v) {
     x += v.x;
     y += v.y;
    return *this;
}

Vecteur2D::operator-(Vecteur2D v) {
     x -= v.x;
     y -= v.y;
    return *this;
}

Vecteur2D::operator*(Vecteur2D v) {
     x = x*v.x;
     y = x*v.y;
    return *this;
}

Vecteur2D::operator/(Vecteur2D v) {
    if((v.x != 0) && (v.y != 0)) {
        x = x/v.x;
        y = x/v.y;
    }
    return *this;
}