class menu {

    private : 
        Scores * scores;
        struct Scores {
            int score;
            char date;
        };

    public : 
        recupScoreFromFile(); ///récupère le score depuis un fichier externe
        trieScore(); /// trie les scores 
};