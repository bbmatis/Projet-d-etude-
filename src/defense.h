using namespace std;

enum typeDef {CANNON, DOUBLECANNON, MORTIER};

class Defense {
    private: 
        float reloadTime;
        unsigned int damage;
        bool zoneDamage;
        unsigned int range;
        unsigned int level;
    public:
        //! \brief Construit la défense selon le type donné (typeDef) 
        Defense(typeDef type);

        Defense();

        //! \brief Obtenir les dégats que fait la defense
        unsigned int getDamage() const;

        //! \brief Modifier les dégats que fait la defense
        //! \param newDamage Nouveau dégats
        void setDamage(unsigned int newDamage);

        //! \brief Obtenir le temps de recharge de la defense
        float getReloadTime() const;

        //! \brief Modifie le temps de recharge de la defense
        //! \param newReloadTime Nouveau temps de recharge
        void setReloadTime(float newReloadTime);

        //! \brief Définir la portée de la défense
        //! \param newRange Nouvelle portée
        void setRange(unsigned int newRange);

        //! \brief Obtenir la portée de la défense
        unsigned int getRange() const;

        //! \brief Attaque le/les montres autour d'elle même
        void attackNearby() const ;

        //! \brief Améliorer la défense au niveau supérieur
        void Ameliorer();
        
};

