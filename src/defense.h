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

        //! \brief Obtenir la zone de dégats de la defense
        bool getZoneDamage() const;

        //! \brief Obtenir le temps de recharge de la defense
        float getReloadTime() const;

        //! \brief Modifier les dégats que fait la defense
        unsigned int setDamage(unsigned int new_damage);

        //! \brief Modifier la zone de dégats de la defense
        bool setZoneDamage(bool new_zoneDamage);

        //! \brief Modifie le temps de recharge de la defense
        float setReloadTime(float new_reloadTime);

        //! \brief Attaque le/les montres autour suivant les type 
        void attackNearby() const ;

        void Ameliorer() const;
        
};

