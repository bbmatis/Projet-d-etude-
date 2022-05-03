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
        unsigned int dimx, dimy; // Dimentions X et Y de l'image
        SDL_Window * window; // Fenêtre SDL
        SDL_Renderer * renderer; // Renderer SDL
        
        TTF_Font * font;
        Image font_im; 
        SDL_Color Couleur_Texte; 
        SDL_Event events;
        
        
        int retour;
        bool choix;
        bool display=true;
        bool AfficherInfosSansMenus =true;
        bool lancervague=false;
        bool AfficherMenuChoixShopBool=false;
        bool AfficherMenuChoixBuyDefBool=false;
        bool AfficherMenuChoixUpgSellBool=false;
        bool AfficherCroix = false;
        bool AfficherCercleRange = false;
        bool AfficheRectangleHover = false;
        bool AfficherErreursBool = false;
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
        int temps=0;
        int currenttime = 0;
        float deltatime = 0.f;

        //On initalise des position et largeur prédefinie pour simplifier la gestion des menus
        int ParamInitShop[4] = {DimWindowX/2-45, DimWindowY -95, 90, 60};
        int ParamInitUpgrade[4] = {DimWindowX/2+160, DimWindowY -100, 60, 60};
        int ParamInitPlay[4] = {DimWindowX/2-250, DimWindowY -90, 60, 60};
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

        //! \brief afficher le jeu en mode graphique
        void afficherGame();

        //! \brief afficher les prix des défenses
        void afficherPrix();

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
        void AfficherTexte(string Msg, string MsgWithValeur, float Valeur, int x, int y, int w, int h, int r, int g, int b);

        //! \brief Afficher les erreurs 
        void AfficherMessageErreur(int nbErr);

        //! \brief Afficher le jeu dans une fenêtre SDL2
        void afficher();

        //! \brief Initialise SDL
        void afficherInit(); 

        //! \brief Iinitialise l'affichage du plateau de def
        void AffichagePateau(); 
        
        //! \brief Affiche bouton play et infos jeu (vague, monstres tuées...)
        void AfficherInfosJeu();
        
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
