struct Scores {
    int score;
    char date;
};

class menu {

    private : 
        Scores * scores; //Tableau contenant les monstres

    public : 
        void recupScoreFromFile(); /** \brief récupère le score depuis un fichier externe **/
        void trieScore(); /** \brief trie les scores **/
};