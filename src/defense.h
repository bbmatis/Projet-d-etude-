using namespace std;

enum typeDef {CANNON, DOUBLECANNON, MORTIER};

class Defense {
    private: 
        float reloadTime;
        unsigned int damage;
        bool zoneDamage;
    public:
        //! \brief Construit la défense selon le type donné (typeDef) 
        Defense(typeDef type);

        //! \brief Obtenir les dégats que fait la defense
        unsigned int getDamage() const;

        //! \brief Attaque le/les montres autour suivant les type 
        void attackNearby() const ;
};

