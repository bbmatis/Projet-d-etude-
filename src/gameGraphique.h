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
        unsigned int dimx, dimy; //! Dimentions X et Y de l'image
        SDL_Window * window; //! Fenêtre SDL
        SDL_Renderer * renderer; //! Renderer SDL

        TTF_Font * font;

        
        Image font_im; 
        SDL_Color Couleur_Texte; 
        
        
        int retour;
        bool touchemonstre = true;
        bool choix;

        //Utile pour le temps et les frames
        float frametime=0;
        int prevtime = 0;
        int temps=0;
        int currenttime = 0;
        float deltatime = 0.f;

        //On initalise des position et largeur prédefinie pour simplifier la gestion des menus
        int ParamInitShop[4] = {DimWindowX/2-45, 705, 90, 60};
        int ParamInitUpgrade[4] = {DimWindowX/2+160, 700, 60, 60};
        int ParamInitSell[4] = {DimWindowX/2-230, 686, 70, 85};
        int ParamInitShopCANON[4] = {DimWindowX/2-460, DimWindowY-100, 70, 70};
        int ParamInitShopDOUBLECANON[4] = {DimWindowX/2-150, DimWindowY-100, 70, 70};
        int ParamInitShopMORTIER[4] = {DimWindowX/2+160, DimWindowY-100, 70, 70};
        

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

    public:
        
        //! \brief Constructeur
        GameGraphique(Game theGame);

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

        //! \brief Afficher l'image de la console
        void AfficherTexte(string Msg, string MsgWithValeur, float Valeur, int x, int y, int w, int h, int r, int g, int b);

        //! \brief Afficher les erreurs 
        void AfficherMessageErreur(int nbErr);

        //! \brief Afficher l'image dans une fenêtre SDL2
        void afficher();

        void afficherInit(); //! Initialise SDL
        void AffichagePateau(); //Iinitialise l'affichage du plateau de def
        void AfficherMenuChoixShop(); //Affiche le menu pour les choix pour une case vide -> just shop
        void AfficherMenuBuyDef(); //Affiche le menu pour choisir la défense à acheter 
        void AfficherShopInfoDefense(typeDef type, int posx, int posy, int w, int h); //Affiche les infos d'une défense en texte en fonction du type de def -> shop buy
        void AfficherInfosDefenseSelected(Defense def, int CaseChoisie ,int posX, int posY, int W, int H); //Affiche les infos d'une defense déja posé
        void AfficherMenuChoixUpgSell(); //Affiche le menu pour les choix pour une case rempli -> sell and upgrade
        void afficherBoucle();  //! Boucle d'affichage de l'image
        void afficherErreurs();

};

#endif
