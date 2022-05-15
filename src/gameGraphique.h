#ifndef GAMEGRAPHIQUE_H
#define GAMEGRAPHIQUE_H

#include "game.h"
#include "Menu.h"
#include "Image.h"

#include <stdlib.h>
#include <SDL2/SDL.h>  
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define DimWindowX 1000
#define DimWindowY 800


// ===== GameGraphique ===== //

class GameGraphique {

    private: 
        Game game;
        Menu menu;
        Joueur joueur;
        unsigned int dimx, dimy; // Dimentions X et Y de l'image
        SDL_Window * window; // Fenêtre SDL
        SDL_Renderer * renderer; // Renderer SDL
        
        TTF_Font * font_default;
        TTF_Font * font_vie;
        TTF_Font * font_infos;
        SDL_Color Couleur_Texte; 
        SDL_Event events;
        
        
        int retour;
        bool choix;
        bool AfficherInfosSansMenus =true;
        int lancervague=0;
        bool AfficherMenuChoixShopBool=false;
        bool AfficherMenuChoixBuyDefBool=false;
        bool AfficherMenuChoixUpgSellBool=false;
        bool AfficherCroix = false;
        bool AfficherCercleRange = false;
        bool AfficheRectangleHover = false;
        bool AfficherErreursBool = false;
        bool AfficherImageUpgrade = false; 
        int CaseChoisie;
        int PosXRectHover;
        int PosYRectHover;
        int xMouse, yMouse;
        int RangeDefSelected;
        const int tailleCase = 37;


        //Utile pour le temps et les frames
        int totalFrames = 0;
        int frames = 0;
        float frametime=0;
        int prevtime = 0;
        int currenttime = 0;
        float deltatime = 0.f;

        //On initalise des position et largeur prédefinie pour simplifier la gestion des menus
        int ParamInitShop[4] = {DimWindowX/2-45, DimWindowY -95, 90, 60};
        int ParamInitUpgrade[4] = {DimWindowX/2+160, DimWindowY -100, 60, 60};
        int ParamInitPlay[4] = {DimWindowX/2-30, DimWindowY -90, 60, 60};
        int ParamInitSell[4] = {DimWindowX/2-230, 686, 70, 85};
        int ParamInitShopCANON[4] = {DimWindowX/2-460, DimWindowY-100, 70, 70};
        int ParamInitShopDOUBLECANON[4] = {DimWindowX/2-150, DimWindowY-100, 70, 70};
        int ParamInitShopMORTIER[4] = {DimWindowX/2+160, DimWindowY-100, 70, 70};
        
        Image im_plateauFond;
        Image im_monstre1;
        Image im_monstre2;
        Image im_monstre3;
        Image im_defenseDOUBLECANON;
        Image im_defenseCANON;
        Image im_defenseMORTIER;
        Image im_defenseRIEN;
        Image im_hearts;
        Image im_hearts1;
        Image im_hearts2;
        Image im_hearts3;
        Image im_shop;
        Image im_Money;
        Image im_Sell;
        Image im_Upgrade;
        Image im_Cross;
        Image im_Play;
        Image im_CercleRange;
        Image im_rectangleHover;
        Image im_FondMenu;
        Image im_Menu;
        Image im_MenuGreenButton;
        Image im_MenuOrangeButton;
        Image im_HighScores;
        Image im_GameOver;
        
        Mix_Chunk *SonMonstreTue;//Creation d'un pointeur pour stocker un .WAV
        Mix_Music *MusiqueFondMenu;//Création du pointeur de type Mix_Music


    public:
        
        //! \brief Constructeur
        GameGraphique();

        //! \brief Destructeur
        ~GameGraphique();

        /*! \brief Obtient la dimention X de l'image
         */
        unsigned int getDimX();
        
        /*! \brief Obtient la dimention Y de l'image
         */
        unsigned int getDimY();

        //! \brief Afficher du texte sur la fenêtre
        //! \param Msg Texte à afficher (si il n'y a pas de valeur à afficher, ex: "Hello") 
        //! \param MsgWithValeur Texte qui accompagne une valeur ex: "Damage : " + Valeur
        //! \param Valeur Valeur à afficher en Texte
        //! \param x position en x du texte
        //! \param y position en y du texte
        //! \param w largeur du texte
        //! \param h longueur du texte
        //! \param r Couleur rouge
        //! \param g Couleur verte
        //! \param b Couleur bleue
        void AfficherTexte(TTF_Font*font, string Msg, string MsgWithValeur, float Valeur, int x, int y, int r, int g, int b);

        //! \brief Afficher les erreurs 
        void AfficherMessageErreur(int nbErr);

        //! \brief Afficher les scores
        void AfficherLesScores();

        //! \brief Afficher le jeu dans une fenêtre SDL2
        void afficher();

        //! \brief Afficher le menu
        //! \return false si le joueur quitte le jeu
        bool afficherMenu();

        //! \brief Afficher le jeu
        //! \return false si le joueur quitte le jeu
        bool afficherGame();

        //! \brief Afficher le paneau de game over
        //! \return false si le joueur quitte le jeu
        bool afficherGameOver();

        //! \brief Initialise SDL
        void afficherInit(); 

        //! \brief Iinitialise l'affichage du plateau de def
        void AffichagePateau(); 
        
        //! \brief Affiche bouton play et infos jeu (vague, monstres tuées...)
        void AfficherInfosJeu();

        //! \brief Affiche les images des defenses améliorées
        void AfficherDefenseUpgrade(Defense defense); 
        
        //! \brief Affiche le menu pour les choix pour une case vide -> just shop
        void AfficherMenuChoixShop();
        
        //! \brief Affiche le menu pour choisir la défense à acheter 
        void AfficherMenuBuyDef();
        
        //! \brief Affiche les infos d'une défense en texte en fonction du type de def -> shop buy
        //! \param type type de la défense auquel on veut afficher les infos 
        //! \param posx position en x du texte 
        //! \param posy position en y du texte
        //! \param w largeur du texte
        //! \param h longueur du texte
        void AfficherShopInfoDefense(typeDef type, int posx, int posy, int w, int h); 
        
        //! \brief Affiche les infos d'une defense déja posé
        //! \param def Defense auquel on veut afficher les infos 
        //! \param CaseChoisie indice de la case où se trouve la defense
        //! \param posX position en x du texte 
        //! \param posY position en y du texte
        //! \param W largeur du texte
        //! \param H longueur du texte
        void AfficherInfosDefenseSelected(Defense def, int CaseChoisie ,int posX, int posY, int W, int H);
        
        //! \brief Affiche le menu pour les choix pour une case rempli -> sell and upgrade
        void AfficherMenuChoixUpgSell();

        //! \brief Affiche les erreurs sur l'écran
        void afficherErreurs();


};

#endif
