class menu {

    private : 
        Scores * scores; /** \param scores Tableau contenant les monstres **/
        struct Scores {
            int score;
            char date;
        };

    public : 
        void recupScoreFromFile(); /** \brief récupère le score depuis un fichier externe **/
        void trieScore(); /** \brief trie les scores **/
};