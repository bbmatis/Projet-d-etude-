#include "gameGraphique.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <cmath>

GameGraphique::GameGraphique()
{
    unsigned int leModeDAffichage = 1;
    Game laGame(leModeDAffichage);
    laGame.init();
    game = laGame;
}

GameGraphique::~GameGraphique()
{

    TTF_CloseFont(font);
    TTF_CloseFont(font_vie);
    TTF_CloseFont(font_infos);
    TTF_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
}

// Affiche du texte selon l'entrée
void GameGraphique::AfficherTexte(TTF_Font *font, string Msg, string MsgWithValeur, float Valeur, int x, int y, int r, int g, int b)
{

    SDL_Color color = {r, g, b};
    const char *text = Msg.c_str();

    if (Msg == "")
    {
        ostringstream Val;
        Val << Valeur;
        string val = MsgWithValeur + Val.str();
        text = val.c_str();
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int w, h = 24;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dstrect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Initialise SDL TTF FONT Window Render + Elements du jeu (Image...)
void GameGraphique::afficherInit()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("SUPER MEGA ULTRA GIGA AWESOME AND SO COOOOL RANDOMLY GENERATED GAME NAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() < 0)
    {
        cout << "Erreur lors de l'initialisation de TTF" << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // FONTS
    font = TTF_OpenFont("img/arial.ttf", 24);
    if (font == nullptr)
        font = TTF_OpenFont("img/arial.ttf", 24);
    if (font == nullptr)
    {
        cout << "Failed to load img/Arial.ttf SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    font_vie = TTF_OpenFont("img/arial.ttf", 10);
    font_infos = TTF_OpenFont("img/arial.ttf", 20);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    im_plateauFond.loadFromFile("img/PlateauFond_old.png", renderer);
    im_monstre1.loadFromFile("img/Squelette.png", renderer);
    im_monstre2.loadFromFile("img/monstre2.png", renderer);
    im_monstre3.loadFromFile("img/Golem.png", renderer);
    im_defenseCANON.loadFromFile("img/CANON.png", renderer);
    im_defenseDOUBLECANON.loadFromFile("img/DoubleCanon.png", renderer);
    im_defenseMORTIER.loadFromFile("img/Mortier.png", renderer);
    im_defenseRIEN.loadFromFile("img/dirt.png", renderer);
    im_hearts.loadFromFile("img/Coeur_Complet.png", renderer);
    im_hearts1.loadFromFile("img/Coeur-1.png", renderer);
    im_hearts2.loadFromFile("img/Coeur-2.png", renderer);
    im_hearts3.loadFromFile("img/Coeur-3.png", renderer);
    im_Money.loadFromFile("img/Money.png", renderer);
    im_shop.loadFromFile("img/Shop.png", renderer);
    im_Sell.loadFromFile("img/Sell.png", renderer);
    im_Upgrade.loadFromFile("img/Upgrade.png", renderer);
    im_Cross.loadFromFile("img/Cross.png", renderer);
    im_Play.loadFromFile("img/Play.png", renderer);
    im_CercleRange.loadFromFile("img/CircleRange.png", renderer);
    im_rectangleHover.loadFromFile("img/RectangleHover.png", renderer);
    im_FondMenu.loadFromFile("img/FondMenu.png", renderer);
    im_Menu.loadFromFile("img/MenuMenu.png", renderer);
    im_MenuGreenButton.loadFromFile("img/BoutonVertMenu.png", renderer);
    im_MenuOrangeButton.loadFromFile("img/BoutonOrangeMenu.png", renderer);
    im_HighScores.loadFromFile("img/HighScores.png", renderer);
    im_GameOver.loadFromFile("img/GameOver.png", renderer);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
    SDL_RenderClear(renderer);

    // Dessine le plateau de jeu une premiere fois

    AffichagePateau();
}

// Affiche le plateau de jeu
void GameGraphique::AffichagePateau()
{

    int decalagePlateauX = 40;
    int decalagePlateauY = 122;
    im_plateauFond.draw(renderer, 30, 111, 945, 575);

    for (unsigned int j = 0; j < game.defenses.size(); j++)
    {
        int Defy = j / 25;                               // transforme la position en y
        int Defx = j % 25;                               // transforme la position en x
        int posX = Defx * tailleCase + decalagePlateauX; // calcul la position en x
        int posY = Defy * tailleCase + decalagePlateauY; // calcul la position en y
        if (j == 175 || j == 199)
            continue;
        if (game.defenses[j].getType() == RIEN)
        {
            im_defenseRIEN.draw(renderer, posX, posY, 35, 35);
        }
        else if (game.defenses[j].getType() == DOUBLECANON)
        {
            im_defenseDOUBLECANON.draw(renderer, posX, posY, 35, 35);
        }
        else if (game.defenses[j].getType() == CANON)
        {
            im_defenseCANON.draw(renderer, posX, posY, 35, 35);
        }
        else if (game.defenses[j].getType() == MORTIER)
        {
            im_defenseMORTIER.draw(renderer, posX, posY, 35, 35);
        }
    }

    for (unsigned int i = 0; i < game.monstres.size(); i++)
    {
        int monstreX = game.monstres[i].getPosition().x + decalagePlateauX;
        int monstreY = game.monstres[i].getPosition().y + decalagePlateauY;
        // Si le monstre as déjà reçu des dégats
        if (game.monstres[i].getHp() < game.monstres[i].getMaxHp())
        {
            // Détermine la taille de la barre de vie
            int hp = game.monstres[i].getHp();
            int maxHp = game.monstres[i].getMaxHp();
            int hpBar = (hp * 100 / maxHp) / 2;
            SDL_Rect LifeRect = {monstreX - 8, monstreY - 5, hpBar, 5};

            SDL_RenderFillRect(renderer, &LifeRect);
            AfficherTexte(font_vie, "", "", hp, monstreX - 12, monstreY - 12, 0, 0, 0);
        }

        if (game.monstres[i].getType() == Mob1)
        {
            im_monstre1.draw(renderer, monstreX, monstreY, 35, 35);
        }
        if (game.monstres[i].getType() == Mob2)
        {
            im_monstre2.draw(renderer, monstreX, monstreY, 35, 35);
        }
        if (game.monstres[i].getType() == Mob3)
        {
            im_monstre3.draw(renderer, monstreX, monstreY, 35, 35);
        }
    }

    // affichage de la money
    im_Money.draw(renderer, 50, 50, 50, 50);

    AfficherTexte(font, "", "", game.joueur.money, 120, 60, 125, 125, 0);

    //===============Afficher le temps===================================================

    temps = (SDL_GetTicks() / 1000.f); // récup le temps toute les secondes
    AfficherTexte(font, "", "", temps, 900, 60, 0, 0, 0);
    // Gère le système d'affichage de vie

    if (game.joueur.getNbVies() == 3)
        im_hearts.draw(renderer, DimWindowX / 2 - 90, DimWindowY - 760, 180, 60);
    if (game.joueur.getNbVies() == 2)
        im_hearts1.draw(renderer, DimWindowX / 2 - 90, DimWindowY - 760, 180, 60);
    if (game.joueur.getNbVies() == 1)
        im_hearts2.draw(renderer, DimWindowX / 2 - 90, DimWindowY - 760, 180, 60);
    if (game.joueur.getNbVies() < 1)
        im_hearts3.draw(renderer, DimWindowX / 2 - 90, DimWindowY - 760, 180, 60);
}

void GameGraphique::AfficherInfosJeu()
{
    im_Play.draw(renderer, ParamInitPlay[0], ParamInitPlay[1], ParamInitPlay[2], ParamInitPlay[3]);

    AfficherTexte(font_infos, "", "Tues : ", game.nbMonstreTues, ParamInitPlay[0] + ParamInitPlay[2] + 20, ParamInitPlay[1], 0, 0, 0);

    AfficherTexte(font_infos, "", "Vague : ", game.vague, ParamInitPlay[0] + ParamInitPlay[2] + 20, ParamInitPlay[1] + 26, 0, 0, 0);
    
    AfficherTexte(font_infos, "", "Monstres : ", game.vague * 4, ParamInitPlay[0] + ParamInitPlay[2] + 20, ParamInitPlay[1] + 55, 0, 0, 0);
}

// Affiche le menu pour les choix
void GameGraphique::AfficherMenuChoixShop()
{

    im_shop.draw(renderer, ParamInitShop[0], ParamInitShop[1], ParamInitShop[2], ParamInitShop[3]); // acheter une défense
    AfficherTexte(font_infos, "Shop", "", 0, ParamInitShop[0] + 20, ParamInitShop[1] + 65, 0, 0, 0);
}

// Affiche les infos d'une defense selectionnée
void GameGraphique::AfficherInfosDefenseSelected(Defense def, int CaseChoisies, int posX, int posY, int W, int H)
{

    AfficherTexte(font_infos, "", "Case : ", CaseChoisies, posX - 45, posY, 0, 0, 0);

    int type = def.getType();
    string Type;
    switch (type)
    {
    case 1:
        Type = "CANON";
        break;
    case 2:
        Type = "DOUBLECANON";
        break;
    case 3:
        Type = "MORTIER";
        break;
    }
    AfficherTexte(font_infos, Type, "", 0, posX - 55, posY + 20, 0, 0, 0);

    AfficherTexte(font_infos, "", "Damage : ", def.getDamage(), posX - W / 2, posY + 40, 0, 0, 0);

    AfficherTexte(font_infos, "", "Range : ", def.getRange(), posX - W / 2 + 5, posY + 60, 0, 0, 0);

    AfficherTexte(font_infos, "", "AtkSpeed : ", def.getReloadTime(), posX - W / 2, posY + 80, 0, 0, 0);

    AfficherTexte(font_infos, "", "Level : ", def.getLevel(), posX - W / 2 + 10, posY + 100, 0, 0, 0);
}

// Affiche les infos des différent types de def pour le shop
void GameGraphique::AfficherShopInfoDefense(typeDef type, int posx, int posy, int w, int h)
{

    switch (type)
    {
    case CANON:

        AfficherTexte(font_infos, "Damage : 5", "", 0, posx + h, posy, 0, 0, 0);
        AfficherTexte(font_infos, "Range : 3", "", 0, posx + h, posy + h, 0, 0, 0);
        AfficherTexte(font_infos, "AtkSpeed : 0.5s", "", 0, posx + h, posy + 2 * h, 0, 0, 0);
        AfficherTexte(font_infos, "50", "", 0, posx + w + 70, posy + 10, 0, 0, 0);

        im_Money.draw(renderer, posx + w + 105, posy + 10, 25, 25);

        break;

    case DOUBLECANON:

        AfficherTexte(font_infos, "Damage : 10", "", 0, posx + h, posy, 0, 0, 0);
        AfficherTexte(font_infos, "Range : 2", "", 0, posx + h, posy + h, 0, 0, 0);
        AfficherTexte(font_infos, "AtkSpeed : 0.25s", "", 0, posx + h, posy + 2 * h, 0, 0, 0);
        AfficherTexte(font_infos, "100", "", 0, posx + w + 60, posy + 10, 0, 0, 0);

        im_Money.draw(renderer, posx + w + 105, posy + 10, 25, 25);

        break;

    case MORTIER:

        AfficherTexte(font_infos, "Damage : 25", "", 0, posx + h, posy, 0, 0, 0);
        AfficherTexte(font_infos, "Range : 4", "", 0, posx + h, posy + h, 0, 0, 0);
        AfficherTexte(font_infos, "AtkSpeed : 2s", "", 0, posx + h, posy + 2 * h, 0, 0, 0);
        AfficherTexte(font_infos, "200", "", 0, posx + w + 60, posy + 10, 0, 0, 0);

        im_Money.draw(renderer, posx + w + 105, posy + 10, 25, 25);

        break;

    default:
        break;
    }
}

// Affiche le menu pour acheter des défenses
void GameGraphique::AfficherMenuBuyDef()
{

    //===================Canon======================
    im_defenseCANON.draw(renderer, ParamInitShopCANON[0], ParamInitShopCANON[1], ParamInitShopCANON[2], ParamInitShopCANON[3]);
    AfficherTexte(font_infos, "CANON", "", 0, ParamInitShopCANON[0], ParamInitShopCANON[1] + 70, 0, 0, 0);
    AfficherShopInfoDefense(CANON, ParamInitShopCANON[0] + 60, ParamInitShopCANON[1], 100, 20);

    //===================DoubleCanon======================
    im_defenseDOUBLECANON.draw(renderer, ParamInitShopDOUBLECANON[0], ParamInitShopDOUBLECANON[1], ParamInitShopDOUBLECANON[2], ParamInitShopDOUBLECANON[3]);
    AfficherTexte(font_infos, "DOUBLECANON", "", 0, ParamInitShopDOUBLECANON[0] - 30, ParamInitShopDOUBLECANON[1] + 70, 0, 0, 0);
    AfficherShopInfoDefense(DOUBLECANON, ParamInitShopDOUBLECANON[0] + 70, ParamInitShopDOUBLECANON[1], 100, 20);

    //===================Mortier======================

    im_defenseMORTIER.draw(renderer, ParamInitShopMORTIER[0], ParamInitShopMORTIER[1], ParamInitShopMORTIER[2], ParamInitShopMORTIER[3]);
    AfficherTexte(font_infos, "MORTIER", "", 0, ParamInitShopMORTIER[0] - 5, ParamInitShopMORTIER[1] + 70, 0, 0, 0);
    AfficherShopInfoDefense(MORTIER, ParamInitShopMORTIER[0] + 60, ParamInitShopMORTIER[1], 100, 20);
}

// Affiche le menu pour vendre ou améliorer une défense
void GameGraphique::AfficherMenuChoixUpgSell()
{

    im_Sell.draw(renderer, ParamInitSell[0], ParamInitSell[1], ParamInitSell[2], ParamInitSell[3]); // Vendre une défenses
    AfficherTexte(font_infos, "Vendre la defense", "", 0, ParamInitSell[0] - 160, ParamInitSell[1] + 35, 0, 0, 0);

    im_Upgrade.draw(renderer, ParamInitUpgrade[0], ParamInitUpgrade[1], ParamInitUpgrade[2], ParamInitUpgrade[3]); // Améliorer une défense
    AfficherTexte(font_infos, "Ameliorer la defense", "", 0, ParamInitUpgrade[0] + 70, ParamInitUpgrade[1] + 20, 0, 0, 0);
}

void GameGraphique::AfficherDefenseUpgrade(Defense defense)
{
    //============================A REFAIRE==================================

    /*     int Y = 120;
        int X = 40;
        int Tcase = 37;
        if(AfficherImageUpgrade == true) {
            if(defense.getType() == CANON) {
                //im_UpgradeCANON.draw(renderer,posX, posY, 35, 35);
                AfficherTexte(font, "1","",0,5*Tcase+X+10,5*Tcase+Y+8,0,100,200);
            }
            if(defense.getType() == DOUBLECANON) {
                //im_UpgradeDOUBLECANON.draw(renderer,posX, posY, 35, 35);
                AfficherTexte(font, "1","",0,5*Tcase+X+10,5*Tcase+Y+8,0,0,255);
            }
            if(defense.getType() == MORTIER) {
                //im_UpgradeMORTIER.draw(renderer,posX, posY, 35, 35);
                AfficherTexte(font, "1","",0,5*Tcase+X+10,5*Tcase+Y+8,0,0,255);
            }
        } */
}

// Affiche les message d'erreur
void GameGraphique::AfficherMessageErreur(int nbErr)
{
    string err2 = "Le level max est atteint par la defense !";
    string err3 = "Vous n'avez pas assez d'argent pour acheter cette defense !";
    string err4 = "Impossible de bloquer le chemin des monstres !";
    string err = "";

    if (nbErr == -4)
    {
        err = err4;
    }
    if (nbErr == -2)
    {
        err = err2;
    }
    if (nbErr == -3)
    {
        err = err3;
    }

    AfficherTexte(font_infos, err.c_str(), "", 0, 50, 700, 255, 50, 50);
}

// Boucle du jeu
void GameGraphique::afficher()
{

    afficherInit();
    bool fenetreOuverte = true;
    while (fenetreOuverte)
    {
        // Le menu
        fenetreOuverte = afficherMenu();
        if (!fenetreOuverte)
            continue;

        // Le jeu
        fenetreOuverte = afficherGame();
        if (!fenetreOuverte)
            continue;

        // Game Over
        fenetreOuverte = afficherGameOver();
    }
}

// Afficher le menu
bool GameGraphique::afficherMenu()
{
    bool displayMenu = true;
    bool displayScores = false;
    bool AfficheRectangleHoverButton = false;
    int xMouse, yMouse;
    int posx, posy; // pour le rect hover
    SDL_Event events;

    while (displayMenu)
    {
        im_FondMenu.draw(renderer, 0, 0, DimWindowX, DimWindowY);
        im_Menu.draw(renderer, 250, 20, 500, 700);
        // SDL_RenderDrawLine(renderer, 500, 0, 500, 800);
        // SDL_RenderDrawLine(renderer, 0, 400, 1000, 400);

        im_MenuGreenButton.draw(renderer, 400, 375, 200, 50);
        AfficherTexte(font, "Jouer", "", 0, 468, 385, 0, 0, 0);

        im_MenuGreenButton.draw(renderer, 400, 460, 200, 50);
        AfficherTexte(font, "Regles", "", 0, 462, 470, 0, 0, 0);

        im_MenuOrangeButton.draw(renderer, 400, 545, 200, 50);
        AfficherTexte(font, "Quitter le jeu", "", 0, 430, 555, 0, 0, 0);

        im_MenuOrangeButton.draw(renderer, 775, 725, 200, 50);
        AfficherTexte(font, "Scores", "", 0, 840, 735, 0, 0, 0);

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                return false;

            SDL_GetMouseState(&xMouse, &yMouse);
            if (events.type == SDL_MOUSEMOTION)
            {
                if (xMouse > 400 && yMouse > 375 && xMouse < 600 && yMouse < 425)
                {
                    AfficheRectangleHoverButton = true;
                    posx = 400;
                    posy = 375;
                }
                else if (xMouse > 400 && yMouse > 460 && xMouse < 600 && yMouse < 510)
                {
                    AfficheRectangleHoverButton = true;
                    posx = 400;
                    posy = 460;
                }
                else if (xMouse > 400 && yMouse > 545 && xMouse < 600 && yMouse < 595)
                {
                    AfficheRectangleHoverButton = true;
                    posx = 400;
                    posy = 545;
                }
                else if (xMouse > 775 && yMouse > 725 && xMouse < 975 && yMouse < 775)
                {
                    AfficheRectangleHoverButton = true;
                    posx = 775;
                    posy = 725;
                }
                else
                    AfficheRectangleHoverButton = false;
            }

            if (events.type == SDL_MOUSEBUTTONDOWN)
            {

                if (displayScores == false)
                {
                    if (xMouse > 400 && yMouse > 375 && xMouse < 600 && yMouse < 425)
                    {

                        return true;
                        cout << "Lance le jeu" << endl;
                    }
                    if (xMouse > 400 && yMouse > 460 && xMouse < 600 && yMouse < 510)
                    {

                        cout << "Ouvre les regles" << endl;
                    }
                    if (xMouse > 400 && yMouse > 545 && xMouse < 600 && yMouse < 595)
                    {
                        cout << "Quitte le jeu" << endl;
                        return false;
                    }
                    if (xMouse > 775 && yMouse > 725 && xMouse < 975 && yMouse < 775)
                    {
                        cout << "Afficher Tab Scores" << endl;
                        displayScores = true;
                    }
                }
                if (displayScores)
                {
                    if (xMouse > 740 && yMouse > 190 && xMouse < 760 && yMouse < 210)
                    {
                        displayScores = false;
                    }
                }
            }
        }
        if (displayScores)
        {

            AfficherLesScores();
        }
        if (AfficheRectangleHoverButton)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 80);
            SDL_Rect RectHoverButton = {posx, posy, 200, 50};
            SDL_RenderFillRect(renderer, &RectHoverButton);
        }

        SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    return true;
}
// Afficher le tableau des scores
void GameGraphique::AfficherLesScores()
{
    unsigned int leS = game.recupScoreFromFile();
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 185);
    im_HighScores.draw(renderer, 200, 150, 600, 500);
    im_Cross.draw(renderer, 740, 190, 20, 20);

    AfficherTexte(font, "Nom du Joueur  |", "", 0, 250, 300, 0, 0, 0);
    AfficherTexte(font, joueur.getNom(), "", 0, 250, 350, 0, 0, 0);
    AfficherTexte(font, "Score", "", 0, 450, 300, 0, 0, 0);
    AfficherTexte(font, "", "", leS, 450, 350, 0, 0, 0);
}

// Afficher le paneau de game over
bool GameGraphique::afficherGameOver()
{
    bool displayGameOver = true;
    bool AfficheRectangleHoverButton = false;
    int xMouse, yMouse;
    int posx, posy;
    SDL_Event events;

    while (displayGameOver)
    {
        AffichagePateau();
        SDL_Rect rect = {0, 0, 1000, 800};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
        SDL_RenderFillRect(renderer, &rect);
        im_GameOver.draw(renderer, 100, 250, 800, 100);

        im_MenuGreenButton.draw(renderer, 400, 450, 200, 50);
        AfficherTexte(font, "Retour au menu", "", 0, 416, 459, 0, 0, 0);

        im_MenuOrangeButton.draw(renderer, 400, 550, 200, 50);
        AfficherTexte(font, "Quitter le jeu", "", 0, 430, 559, 0, 0, 0);

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                return false;
            SDL_GetMouseState(&xMouse, &yMouse);
            if (events.type == SDL_MOUSEMOTION)
            {
                if (xMouse > 400 && yMouse > 450 && xMouse < 600 && yMouse < 500)
                {
                    AfficheRectangleHoverButton = true;
                    posx = 400;
                    posy = 450;
                }
                else if (xMouse > 400 && yMouse > 550 && xMouse < 600 && yMouse < 600)
                {
                    AfficheRectangleHoverButton = true;
                    posx = 400;
                    posy = 550;
                }
                else
                    AfficheRectangleHoverButton = false;
            }
            if (events.type == SDL_MOUSEBUTTONDOWN)
            {
                if (xMouse > 400 && yMouse > 450 && xMouse < 600 && yMouse < 500)
                {
                    // On retourne sur le menu
                    return true;
                }
                if (xMouse > 400 && yMouse > 550 && xMouse < 600 && yMouse < 600)
                {
                    // On quitte le jeu
                    return false;
                }
            }
        }
        if (AfficheRectangleHoverButton)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 80);
            SDL_Rect RectHoverButton = {posx, posy, 200, 50};
            SDL_RenderFillRect(renderer, &RectHoverButton);
        }
        SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    return true;
}

// Afficher le jeu
bool GameGraphique::afficherGame()
{
    bool display = true;
    while (display)
    {
        // Met le jeu en pause pdt 10ms pour avoir quelquechose comme 100fps
        this_thread::sleep_for(chrono::milliseconds(10));

        // Affiche les fps dans la console
        frames++;
        totalFrames++;
        if (frametime >= 1.f) // Toute les secondes on affiche le nb de fps
        {
            cout << "FPS : " << frames << " Total : " << totalFrames << endl;
            frames = 0;
            frametime = 0;
        }
        // fonction de frametime
        prevtime = currenttime;
        currenttime = SDL_GetTicks();
        deltatime = (currenttime - prevtime) / 1000.f;
        frametime += deltatime;
        temps=0;
        int temps1;

        AffichagePateau();
        SDL_RenderDrawLine(renderer, 0, 400, 1000, 400);
        SDL_RenderDrawLine(renderer, 500, 0, 500, 800);

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
            {
                display = false;
                return false;
            }
            if (events.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&xMouse, &yMouse); // Recupère pos x et y de la souris
                for (unsigned int i = 0; i < game.defenses.size(); i++)
                {
                    int Defy = i / 25; // transforme la position en i
                    int Defx = i % 25; // transforme la position en j

                    if (i != 175 && i != 199 && xMouse > Defx * tailleCase + 40 && xMouse < Defx * tailleCase + 40 + 35 && yMouse > Defy * tailleCase + 122 && yMouse < Defy * tailleCase + 122 + 35)
                    {
                        AfficheRectangleHover = true;
                        PosXRectHover = Defx * tailleCase + 40;
                        PosYRectHover = Defy * tailleCase + 122;
                        RangeDefSelected = game.defenses[i].getRange() * tailleCase;
                        if (game.defenses[i].getType() != RIEN)
                        {
                            AfficherCercleRange = true;
                        }
                    }
                }
            }
            if (events.type == SDL_MOUSEBUTTONDOWN)
            {
                // cout<<xMouse<<" "<<yMouse<<endl;
                for (unsigned int i = 0; i < game.defenses.size(); i++)
                {
                    int Defy = i / 25; // transforme la position en i
                    int Defx = i % 25; // transforme la position en j

                    // si on enfonce le bouton gauche de la souris et que la souris se trouve dans l'une des cases
                    if (i != 175 && i != 199 && xMouse > Defx * tailleCase + 40 && xMouse < Defx * tailleCase + 40 + 35 && yMouse > Defy * tailleCase + 122 && yMouse < Defy * tailleCase + 122 + 35)
                    {
                        if (events.button.button == SDL_BUTTON_LEFT && game.defenses[i].getType() == RIEN)
                        {
                            AfficherMenuChoixShopBool = true; // Affiche le menu buy
                            AfficherCroix = true;
                            AfficherMenuChoixUpgSellBool = false;
                            AfficherInfosSansMenus = false;
                            CaseChoisie = i;
                        }
                        else if (game.defenses[i].getType() != RIEN)
                        {
                            AfficherMenuChoixUpgSellBool = true; // Affiche le menu pour vendre ou défendre + croix et ferme les autres
                            AfficherCroix = true;                // croix fermeture menu
                            AfficherMenuChoixShopBool = false;
                            AfficherMenuChoixBuyDefBool = false;
                            AfficherInfosSansMenus = false;
                            CaseChoisie = i;
                        }
                    }
                    if (AfficherMenuChoixShopBool == true)
                    {
                        if (xMouse > ParamInitShop[0] && xMouse < ParamInitShop[0] + ParamInitShop[2] && yMouse > ParamInitShop[1] && yMouse < ParamInitShop[1] + ParamInitShop[3])
                        {
                            AfficherMenuChoixShopBool = false;
                            AfficherMenuChoixBuyDefBool = true;
                        }
                    }
                    if (AfficherMenuChoixBuyDefBool == true)
                    {
                        AfficherInfosSansMenus = false;
                        if (xMouse > ParamInitShopCANON[0] && xMouse < ParamInitShopCANON[0] + ParamInitShopCANON[2] && yMouse > ParamInitShopCANON[1] && yMouse < ParamInitShopCANON[1] + ParamInitShopCANON[3])
                        {
                            retour = game.buyDefense(CANON, CaseChoisie);
                            AfficherInfosSansMenus = true;
                            AfficherMenuChoixBuyDefBool = false;
                            AfficherCroix = false;

                            if (retour != 0)
                            {
                                temps1 = SDL_GetTicks() / 1000; // demarre le timer a t secondes
                                AfficherErreursBool = true;     // Afficher le texte d'erreur
                            }
                        }
                        else if (xMouse > ParamInitShopDOUBLECANON[0] && xMouse < ParamInitShopDOUBLECANON[0] + ParamInitShopDOUBLECANON[2] && yMouse > ParamInitShopDOUBLECANON[1] && yMouse < ParamInitShopDOUBLECANON[1] + ParamInitShopDOUBLECANON[3])
                        {
                            retour = game.buyDefense(DOUBLECANON, CaseChoisie);
                            AfficherMenuChoixBuyDefBool = false;
                            AfficherCroix = false;
                            AfficherInfosSansMenus = true;
                            if (retour != 0)
                            {
                                temps1 = SDL_GetTicks() / 1000;
                                AfficherErreursBool = true;
                            }
                        }
                        else if (xMouse > ParamInitShopMORTIER[0] && xMouse < ParamInitShopMORTIER[0] + ParamInitShopMORTIER[2] && yMouse > ParamInitShopMORTIER[1] && yMouse < ParamInitShopMORTIER[1] + ParamInitShopMORTIER[3])
                        {
                            retour = game.buyDefense(MORTIER, CaseChoisie);
                            AfficherMenuChoixBuyDefBool = false;
                            AfficherCroix = false;
                            AfficherInfosSansMenus = true;
                            if (retour != 0)
                            {
                                temps1 = SDL_GetTicks() / 1000;
                                AfficherErreursBool = true;
                            }
                        }
                    }
                    if (AfficherMenuChoixUpgSellBool == true)
                    {
                        if (xMouse > ParamInitSell[0] - 180 && xMouse < ParamInitSell[0] + ParamInitSell[2] && yMouse > ParamInitSell[1] && yMouse < ParamInitSell[1] + ParamInitSell[3])
                        {
                            retour = game.sellDefense(game.defenses[CaseChoisie]);
                            AfficherMenuChoixUpgSellBool = false;
                            AfficherCroix = false;
                            AfficherInfosSansMenus = true;
                        }
                        if (xMouse > ParamInitUpgrade[0] && xMouse < ParamInitUpgrade[0] + ParamInitUpgrade[2] + 240 && yMouse > ParamInitUpgrade[1] && yMouse < ParamInitUpgrade[1] + ParamInitUpgrade[3])
                        {
                            retour = game.upgradeDefense(game.defenses[CaseChoisie]);
                            AfficherImageUpgrade = true;
                            AfficherMenuChoixUpgSellBool = false;
                            AfficherCroix = false;
                            AfficherInfosSansMenus = true;
                            if (retour == -2)
                            {
                                temps1 = SDL_GetTicks() / 1000;
                                AfficherErreursBool = true;
                            }
                        }
                    }
                    if (AfficherCroix == true)
                    {
                        if (xMouse > DimWindowX - 40 && xMouse < DimWindowX - 40 + 20 && yMouse > DimWindowY - 100 && yMouse < DimWindowY - 100 + 20)
                        {
                            AfficherCroix = false;
                            AfficherMenuChoixUpgSellBool = false;
                            AfficherMenuChoixBuyDefBool = false;
                            AfficherMenuChoixShopBool = false;
                            AfficherInfosSansMenus = true;
                        }
                    }
                    if (AfficherInfosSansMenus == true && AfficherMenuChoixBuyDefBool == false)
                    {
                        if (xMouse > ParamInitPlay[0] && xMouse < ParamInitPlay[0] + ParamInitPlay[2] && yMouse > ParamInitPlay[1] && yMouse < ParamInitPlay[1] + ParamInitPlay[3])
                        {
                            lancervague = true;
                        }
                    }
                }
            }
        }
        //===============================Lance la vague de monstres==========================================
        if (lancervague == true)
        { // Lancer vague de monstres
            lancervague = game.playTurn();
        }

        //======================Affichage des Menus / Texte / Elements d'infos (MouseHover + RangeCircle)============================================
        if (AfficherErreursBool)
        {
            AfficherMessageErreur(retour);

            if (SDL_GetTicks() / 1000 - temps1 == 3) // Attend 3s avant d'effacer le message d'erreur
            {
                AfficherErreursBool = false;
            }
        }
        if (AfficherCercleRange)
        {
            im_CercleRange.draw(renderer, PosXRectHover + 17 - RangeDefSelected, PosYRectHover + 17 - RangeDefSelected, RangeDefSelected * 2, RangeDefSelected * 2);
        }
        if (AfficheRectangleHover)
        {
            im_rectangleHover.draw(renderer, PosXRectHover, PosYRectHover, 35, 35);
        }
        if (AfficherInfosSansMenus)
        {
            AfficherInfosJeu();
        }
        if (AfficherCroix)
        {
            im_Cross.draw(renderer, DimWindowX - 40, DimWindowY - 100, 20, 20);
        }
        if (AfficherMenuChoixShopBool)
        {
            AfficherMenuChoixShop();
            AfficherTexte(font_infos, "", "Case : ", CaseChoisie, DimWindowX / 2 - 45, 680, 0, 0, 0);
        }
        else if (AfficherMenuChoixBuyDefBool)
        {
            AfficherMenuBuyDef();
        }
        else if (AfficherMenuChoixUpgSellBool)
        {
            AfficherMenuChoixUpgSell();
            AfficherInfosDefenseSelected(game.defenses[CaseChoisie], CaseChoisie, DimWindowX / 2, 680, 100, 30);
            AfficherDefenseUpgrade(game.defenses[CaseChoisie]);
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        game.enregistreScore();
        if (game.isGameOver())
            return true;
    }
    return true;
}