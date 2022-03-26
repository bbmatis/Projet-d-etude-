using namespace std;


enum typeDef {RIEN, CANNON, DOUBLECANNON, MORTIER};

class Defense {
    private: 
        float reloadTime;
        unsigned int damage;
        bool zoneDamage;
        unsigned int range;
        unsigned int level;
        typeDef type;
        //Vecteur2D Position : pour récup la pos d'une def sur le plateau ?
    public:
        //! \fn Constructeur
        //! \param type Type de la défense
        Defense(typeDef type);

        //! \fn Constructeur par défaut
        Defense();

        //! \fn Destructeur
        ~Defense();

        //! \fn Obtenir le prix de la défense
        unsigned int getPrix() const;

        //! \fn Modifier le prix de la défense
        //! \param newPrix Nouveau prix de la défense
        void setPrix(unsigned int newPrix);

        //! \fn Obtenir les dégats que fait la defense
        unsigned int getDamage() const;

        //! \fn Modifier les dégats que fait la defense
        //! \param newDamage Nouveau dégats
        void setDamage(unsigned int newDamage);

        //! \fn Obtenir le temps de recharge de la defense
        float getReloadTime() const;

        //! \fn Modifie le temps de recharge de la defense
        //! \param newReloadTime Nouveau temps de recharge
        void setReloadTime(float newReloadTime);

        //! \fn Définir la portée de la défense
        //! \param newRange Nouvelle portée
        void setRange(unsigned int newRange);

        //! \fn Obtenir la portée de la défense
        unsigned int getRange() const;

        //! \fn Définir le lvl de la défense
        //! \param newLevel Nouveau lvl
        void setLevel(unsigned int newLevel);

        //! \fn Récuper le lvl de la défense
        unsigned int getLevel() const;

        //! \fn Obtenir le type de la défense
        typeDef getType() const;

        //! \fn Attaque le/les montres autour d'elle même
        void attackNearby() const;

        //! \fn Améliorer la défense au niveau supérieur
        void upgrade();



        
};

