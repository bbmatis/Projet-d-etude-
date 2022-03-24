struct Vecteur2D
{
    float x,y;

    const Vecteur2D & operator +(const Vecteur2D PosD) {
       x += PosD.x;
       y += PosD.y;
    }
};

enum TypeMonstres {Mob1, Mob2, Mob3};

class Monstre {

    private:

        
        float speed;
        Vecteur2D position;
        unsigned int nb_vie;

    public:
        
        Monstre(TypeMonstres type, Vecteur2D PosInit);
        ~Monstre();

        void MoveRight();
        void MoveLeft();
        void MoveUp();
        void MoveDown();

        unsigned int getLife();
        void removeLife(int nb);

        Vecteur2D getPos();

        

};