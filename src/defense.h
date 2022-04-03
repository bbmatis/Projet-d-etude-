#ifndef DEFENSE_H
#define DEFENSE_H


enum typeDef {RIEN, CANON, DOUBLECANON, MORTIER};

class Defense {
    private: 
        float reloadTime;       // Temps de rechargement entre 2 attaques
        unsigned int damage;    // Dégats de la défense
        bool zoneDamage;        // Zone de dégats pour le Mortier
        unsigned int range;     // Zone d'attaque de la défense
        unsigned int level;     // Niveau de la défense 
        typeDef type;           // Type de la défense (situé dans le enum)
        unsigned int prix;      // Coût d'achat de la défense 
        
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
        
        //! \fn Améliorer la défense au niveau supérieur
        void upgrade();



        
};

#endif