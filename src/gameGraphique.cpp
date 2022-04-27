#include "gameGraphique.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <thread>

int temps() {
    return int(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}


GameGraphique::GameGraphique(Game theGame) {
  game = theGame;
  
}

GameGraphique::~GameGraphique() {
    
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
}


void GameGraphique::afficherConsole(){
    
}

void GameGraphique::afficherInit() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    window = SDL_CreateWindow("Marine versus the Arabs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DimWindowX, DimWindowY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl; 
        SDL_Quit(); 
        exit(1);
    }

    if(TTF_Init() < 0)
    {
        cout <<"Erreur lors de l'initialisation de TTF" <<TTF_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }

    // FONTS
    font = TTF_OpenFont("img/arial.ttf",50);
    if (font == nullptr)
        font = TTF_OpenFont("img/arial.ttf",50);
    if (font == nullptr) {
            cout << "Failed to load img/Arial.ttf SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}

    game.defenses[186] = Defense(DOUBLECANON); // TEST
    game.defenses[99] = Defense(MORTIER); // TEST 
    game.defenses[254] = Defense(DOUBLECANON); // TEST 
    game.defenses[260] = Defense(CANON); // TEST 
    game.defenses[130] = Defense(DOUBLECANON); // TEST 

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
 
    im_monstre1.loadFromFile("img/Squelette.png", renderer);
    im_monstre2.loadFromFile("img/monstre2.png",renderer);
    im_monstre3.loadFromFile("img/Golem.png", renderer);
    im_defenseCANON.loadFromFile("img/CANON.png",renderer);
    im_defenseDOUBLECANON.loadFromFile("img/DoubleCanon.png", renderer);
    im_defenseMORTIER.loadFromFile("img/Mortier.png", renderer);
    im_defenseRIEN.loadFromFile("img/dirt.png", renderer);
    im_hearts.loadFromFile("img/Coeur_Complet.png", renderer);
    im_hearts1.loadFromFile("img/Coeur-1.png",renderer);
    im_hearts2.loadFromFile("img/Coeur-2.png",renderer);
    im_hearts3.loadFromFile("img/Coeur-3.png", renderer);
    im_Money.loadFromFile("img/Money.png", renderer);
    im_shop.loadFromFile("img/Shop.png",renderer);
    im_Sell.loadFromFile("img/Sell.png",renderer);
    im_Upgrade.loadFromFile("img/Upgrade.png",renderer);

    

    SDL_SetRenderDrawColor(renderer, 238, 230, 211, 255);
    SDL_RenderClear(renderer);

    for(int i=0; i<game.monstres.size(); i++) game.monstres[i].setPosition(0, 400);


    

    // Dessine le plateau de jeu une premiere fois 

    AffichagePateau();

}

void GameGraphique::AffichagePateau(){

    for(unsigned int j=0; j<game.defenses.size(); j++)
    {
        int Defy = j/25; //transforme la position en i
        int Defx = j%25; //transforme la position en j
        if(game.defenses[j].getType() == RIEN)
        {
            im_defenseRIEN.draw(renderer, Defx*37+40, Defy*37+122.5, 35, 35);
        }
        else if(game.defenses[j].getType() == DOUBLECANON)
        {
            im_defenseDOUBLECANON.draw(renderer, Defx*37+40, Defy*37+122.5, 35, 35);
        }
        else if(game.defenses[j].getType() == CANON)
        {
            im_defenseCANON.draw(renderer,Defx*37+40, Defy*37+122.5, 35, 35);
        }
        else if(game.defenses[j].getType() == MORTIER)
        {
            im_defenseMORTIER.draw(renderer,Defx*37+40, Defy*37+122.5, 35, 35);
        }
    }

    

    

    for(unsigned int i =0; i<game.monstres.size(); i++)
    {

       
        if(game.monstres[i].getType() == Mob1){
    
            im_monstre1.draw(renderer,game.monstres[i].getPosition().x,game.monstres[i].getPosition().y, 45, 45);
    
        }
        if(game.monstres[i].getType() == Mob2){

            im_monstre2.draw(renderer,game.monstres[i].getPosition().x,game.monstres[i].getPosition().y, 45, 45);
        } 
        if(game.monstres[i].getType() == Mob3){

            im_monstre3.draw(renderer,game.monstres[i].getPosition().x,game.monstres[i].getPosition().y, 45, 45);
        } 
    }

    //affichage de la money
    im_Money.draw(renderer,50, 50, 50, 50);

    ostringstream ss;
    ss<<game.joueur.money;
    string moula(ss.str());

    Couleur_Texte.r = 125; Couleur_Texte.g = 125; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,moula.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionJouer;
    positionJouer.x = 120; positionJouer.y = 50; positionJouer.w = 50; positionJouer.h = 50;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionJouer);

    //===============Afficher le temps===================================================

    temps = (SDL_GetTicks()/1000.f); //récup le temps toute les secondes
    ostringstream time;
    time<<temps;
    string Time(time.str());

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,Time.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionTime;
    positionTime.x = 900; positionTime.y = 50; positionTime.w = 35; positionTime.h = 35;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTime);

    // Gère le système d'affichage de vie

    if(game.joueur.getNbVies() == 3) im_hearts.draw(renderer, DimWindowX/2-90, DimWindowY-760, 180, 60);
    if(game.joueur.getNbVies() == 2) im_hearts1.draw(renderer,DimWindowX/2-90, DimWindowY-760, 180, 60);
    if(game.joueur.getNbVies() == 1) im_hearts2.draw(renderer,DimWindowX/2-90, DimWindowY-760, 180, 60);
    if(game.joueur.getNbVies() <  1) im_hearts3.draw(renderer,DimWindowX/2-90, DimWindowY-760, 180, 60);
    //TODO Faire pour chaques vie du joueur
}

//Affiche le menu pour les choix
void GameGraphique::AfficherMenuChoixShop(){

    im_shop.draw(renderer, ParamInitShop[0], ParamInitShop[1], ParamInitShop[2],ParamInitShop[3]);//acheter une défense

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,"Shop",Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionShopTxt;
    positionShopTxt.x = ParamInitShop[0]; positionShopTxt.y = ParamInitShop[1]+65; positionShopTxt.w = 80; positionShopTxt.h = 20;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionShopTxt);
   
}

//Affiche les infos d'une defense selectionnée 
void GameGraphique::AfficherInfosDefenseSelected(Defense def, int CaseChoisies,int posX, int posY, int W, int H){


    ostringstream Case;
    Case<<CaseChoisies;
    string CaseChoix("Case : " + Case.str());

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,CaseChoix.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexteInfosSelectedDef_Case;
    positionTexteInfosSelectedDef_Case.x = posX - 45; positionTexteInfosSelectedDef_Case.y = posY; positionTexteInfosSelectedDef_Case.w = 90; positionTexteInfosSelectedDef_Case.h = 20;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosSelectedDef_Case);
    
    
    int type = def.getType();
    string Type;
    switch(type)
    {
        case 1 : 
            Type = "CANON";
            break;
        case 2 : 
            Type = "DOUBLECANON";
            break;
        case 3 : 
            Type = "MORTIER";
            break;
    }
    

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,Type.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexteInfosSelectedDef_dmg;
    positionTexteInfosSelectedDef_dmg.x = posX - 55; positionTexteInfosSelectedDef_dmg.y = posY + 20; positionTexteInfosSelectedDef_dmg.w = 110; positionTexteInfosSelectedDef_dmg.h = 15;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosSelectedDef_dmg);

    
    ostringstream Dmg;
    Dmg<<def.getDamage();
    string Damage("Damage : " + Dmg.str());

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,Damage.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexteInfosSelectedDef_Damage;
    positionTexteInfosSelectedDef_Damage.x = posX - W/2; positionTexteInfosSelectedDef_Damage.y = posY + 40; positionTexteInfosSelectedDef_Damage.w = W; positionTexteInfosSelectedDef_Damage.h = 15;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosSelectedDef_Damage);
    
    
    ostringstream range;
    range<<def.getRange();
    string Range("Range : " + range.str());

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,Range.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexteInfosSelectedDef_range;
    positionTexteInfosSelectedDef_range.x = posX - W/2+5; positionTexteInfosSelectedDef_range.y = posY+60; positionTexteInfosSelectedDef_range.w = W-10; positionTexteInfosSelectedDef_range.h = 15;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosSelectedDef_range);

    
    ostringstream atkSpd;
    atkSpd<<def.getReloadTime();
    string AtkSpeed("AtkSpeed : " + atkSpd.str() + "s");

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,AtkSpeed.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexteInfosSelectedDef_atkSpd;
    positionTexteInfosSelectedDef_atkSpd.x = posX -W/2; positionTexteInfosSelectedDef_atkSpd.y = posY+80; positionTexteInfosSelectedDef_atkSpd.w = W; positionTexteInfosSelectedDef_atkSpd.h = 15;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosSelectedDef_atkSpd);
 
    ostringstream lvl;
    lvl<<def.getLevel();
    string Level("Level : " + lvl.str());

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,Level.c_str(),Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexteInfosSelectedDef_Level;
    positionTexteInfosSelectedDef_Level.x = posX - W/2 +10; positionTexteInfosSelectedDef_Level.y = posY+100; positionTexteInfosSelectedDef_Level.w = W-20; positionTexteInfosSelectedDef_Level.h = 15;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosSelectedDef_Level); 
    
}

//Affiche les infos des différent types de def pour le shop
void GameGraphique::AfficherShopInfoDefense(typeDef type, int posx, int posy, int w, int h){

    switch(type)
    {
        case CANON: 

            //string s = "Damage : 5 \n Range : 5";

            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,"Damage : 5",Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosCANON_dmg;
            positionTexteInfosCANON_dmg.x = posx + h; positionTexteInfosCANON_dmg.y = posy; positionTexteInfosCANON_dmg.w = w; positionTexteInfosCANON_dmg.h = h;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosCANON_dmg);

            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,"Range : 5",Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosCANON_range;
            positionTexteInfosCANON_range.x = posx + h; positionTexteInfosCANON_range.y = posy+h; positionTexteInfosCANON_range.w = w; positionTexteInfosCANON_range.h = h;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosCANON_range);

            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,"AtkSpeed : 0.5s",Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosCANON_atkSpd;
            positionTexteInfosCANON_atkSpd.x = posx + h; positionTexteInfosCANON_atkSpd.y = posy+2*h; positionTexteInfosCANON_atkSpd.w = w; positionTexteInfosCANON_atkSpd.h = h;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosCANON_atkSpd);
            
            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,"50",Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosCANON_price;
            positionTexteInfosCANON_price.x = posx + w + 60; positionTexteInfosCANON_price.y = posy+10; positionTexteInfosCANON_price.w = 40; positionTexteInfosCANON_price.h = 40;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosCANON_price);

            im_Money.draw(renderer, posx + w + 105 , posy + 17 , 25, 25);

            break;

        case DOUBLECANON :

            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,"Damage : 10",Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosDOUBLECANON_dmg;
            positionTexteInfosDOUBLECANON_dmg.x = posx + h; positionTexteInfosDOUBLECANON_dmg.y = posy; positionTexteInfosDOUBLECANON_dmg.w = w; positionTexteInfosDOUBLECANON_dmg.h = h;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosDOUBLECANON_dmg);

            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,"Range : 5",Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosDOUBLECANON_range;
            positionTexteInfosDOUBLECANON_range.x = posx + h; positionTexteInfosDOUBLECANON_range.y = posy+h; positionTexteInfosDOUBLECANON_range.w = w; positionTexteInfosDOUBLECANON_range.h = h;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosDOUBLECANON_range);

            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,"AtkSpeed : 0.25s",Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosDOUBLECANON_atkSpd;
            positionTexteInfosDOUBLECANON_atkSpd.x = posx + h; positionTexteInfosDOUBLECANON_atkSpd.y = posy+2*h; positionTexteInfosDOUBLECANON_atkSpd.w = w; positionTexteInfosDOUBLECANON_atkSpd.h = h;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosDOUBLECANON_atkSpd);
            
            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,"100",Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosDOUBLECANON_price;
            positionTexteInfosDOUBLECANON_price.x = posx + w + 60; positionTexteInfosDOUBLECANON_price.y = posy+10; positionTexteInfosDOUBLECANON_price.w = 40; positionTexteInfosDOUBLECANON_price.h = 40;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosDOUBLECANON_price);

            im_Money.draw(renderer, posx + w + 105 , posy + 17 , 25, 25);

            break;

            case MORTIER :

                Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
                font_im.setSurface(TTF_RenderText_Solid(font,"Damage : 25",Couleur_Texte));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect positionTexteInfosMORTIER_dmg;
                positionTexteInfosMORTIER_dmg.x = posx + h; positionTexteInfosMORTIER_dmg.y = posy; positionTexteInfosMORTIER_dmg.w = w; positionTexteInfosMORTIER_dmg.h = h;
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosMORTIER_dmg);

                Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
                font_im.setSurface(TTF_RenderText_Solid(font,"Range : 6",Couleur_Texte));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect positionTexteInfosMORTIER_range;
                positionTexteInfosMORTIER_range.x = posx + h; positionTexteInfosMORTIER_range.y = posy+h; positionTexteInfosMORTIER_range.w = w; positionTexteInfosMORTIER_range.h = h;
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosMORTIER_range);

                Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
                font_im.setSurface(TTF_RenderText_Solid(font,"AtkSpeed : 2s",Couleur_Texte));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect positionTexteInfosMORTIER_atkSpd;
                positionTexteInfosMORTIER_atkSpd.x = posx + h; positionTexteInfosMORTIER_atkSpd.y = posy+2*h; positionTexteInfosMORTIER_atkSpd.w = w; positionTexteInfosMORTIER_atkSpd.h = h;
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosMORTIER_atkSpd);
                
                Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
                font_im.setSurface(TTF_RenderText_Solid(font,"200",Couleur_Texte));
                font_im.loadFromCurrentSurface(renderer);
                SDL_Rect positionTexteInfosMORTIER_price;
                positionTexteInfosMORTIER_price.x = posx + w + 60; positionTexteInfosMORTIER_price.y = posy+10; positionTexteInfosMORTIER_price.w = 40; positionTexteInfosMORTIER_price.h = 40;
                SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosMORTIER_price);

                im_Money.draw(renderer, posx + w + 105 , posy + 17 , 25, 25);

                break;

            default : break;


    }
}

//Affiche le menu pour acheter des défenses
void GameGraphique::AfficherMenuBuyDef(){
    
    //===================Canon======================
    im_defenseCANON.draw(renderer,ParamInitShopCANON[0], ParamInitShopCANON[1], ParamInitShopCANON[2], ParamInitShopCANON[3]);
    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,"CANON",Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionCANONtxt;
    positionCANONtxt.x = ParamInitShopCANON[0]; positionCANONtxt.y = ParamInitShopCANON[1] + 68; positionCANONtxt.w = 70; positionCANONtxt.h = 30;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionCANONtxt);

    AfficherShopInfoDefense(CANON, ParamInitShopCANON[0] + 60, ParamInitShopCANON[1] , 100, 30 );
    
    //===================DoubleCanon======================
    im_defenseDOUBLECANON.draw(renderer,ParamInitShopDOUBLECANON[0], ParamInitShopDOUBLECANON[1], ParamInitShopDOUBLECANON[2], ParamInitShopDOUBLECANON[3]);
    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,"DOUBLECANON",Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionDOUBLECANONtxt;
    positionDOUBLECANONtxt.x = ParamInitShopDOUBLECANON[0] - 25; positionDOUBLECANONtxt.y = ParamInitShopDOUBLECANON[1] + 68; positionDOUBLECANONtxt.w = 120; positionDOUBLECANONtxt.h = 30;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionDOUBLECANONtxt);

    AfficherShopInfoDefense(DOUBLECANON, ParamInitShopDOUBLECANON[0] + 70, ParamInitShopDOUBLECANON[1], 100, 30);
    
    //===================Mortier======================
    
    im_defenseMORTIER.draw(renderer,ParamInitShopMORTIER[0], ParamInitShopMORTIER[1], ParamInitShopMORTIER[2], ParamInitShopMORTIER[3]);
    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,"MORTIER",Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionMORTIERtxt;
    positionMORTIERtxt.x = ParamInitShopMORTIER[0]; positionMORTIERtxt.y = ParamInitShopMORTIER[1] + 68; positionMORTIERtxt.w = 80; positionMORTIERtxt.h = 30;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionMORTIERtxt);

    AfficherShopInfoDefense(MORTIER, ParamInitShopMORTIER[0] + 60, ParamInitShopMORTIER[1], 100, 30);
}

//Affiche le menu pour vendre ou améliorer une défense 
void GameGraphique::AfficherMenuChoixUpgSell(){

    im_Sell.draw(renderer,ParamInitSell[0], ParamInitSell[1], ParamInitSell[2],ParamInitSell[3]); //Vendre une défenses

    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,"Vendre la defense",Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionSellTxt;
    positionSellTxt.x = ParamInitSell[0]-180; positionSellTxt.y = ParamInitSell[1]+30; positionSellTxt.w = 160; positionSellTxt.h = 40;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionSellTxt);


    im_Upgrade.draw(renderer,ParamInitUpgrade[0], ParamInitUpgrade[1], ParamInitUpgrade[2],ParamInitUpgrade[3]); //Améliorer une défense
    Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
    font_im.setSurface(TTF_RenderText_Solid(font,"Ameliorer la defense",Couleur_Texte));
    font_im.loadFromCurrentSurface(renderer);

    SDL_Rect positionUpgradeTxt;
    positionUpgradeTxt.x = ParamInitUpgrade[0]+90; positionUpgradeTxt.y = ParamInitUpgrade[1]+20; positionUpgradeTxt.w = 200; positionUpgradeTxt.h = 40;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionUpgradeTxt);
}


void GameGraphique::AfficherMessageErreur(int nbErr) {

    string err1 = "Le type de defense n'est pas valide !";
    string err2 = "La position choisie est invalide !";
    string err3 = "Vous n'avez pas assez d'argent pour acheter cette defense !";
    string err = "";

    if(nbErr == -1) {
        err = err1;
    }
    if(nbErr == -2) {
        err = err2;
    }
    if(nbErr == -3) {
        err = err3;
    }

    Couleur_Texte2.r = 250; Couleur_Texte2.g = 50; Couleur_Texte2.b = 55;
    font_im2.setSurface(TTF_RenderText_Solid(font,err.c_str(),Couleur_Texte2));
    font_im2.loadFromCurrentSurface(renderer);

    SDL_Rect positionJouer2;
    positionJouer2.x = 470; positionJouer2.y = 50; positionJouer2.w = 300; positionJouer2.h = 50;
    SDL_RenderCopy(renderer,font_im2.getTexture(),nullptr,&positionJouer2);

}


void GameGraphique::afficherBoucle() {  

    AffichagePateau();
    //AfficherMessageErreur(-2);
}

//Affichage avec le menu de départ 

void GameGraphique::afficher(){

    bool display=true;
    bool lancervague=false;
    bool affichermsg = false;
    bool AfficherMenuChoixShopBool=false;
    bool AfficherMenuChoixBuyDefBool=false;
    bool AfficherMenuChoixUpgSellBool=false;
    int CaseChoisie;
   
    
    int xMouse, yMouse;

    SDL_Event events;
    afficherInit();

    while(display){
         afficherBoucle();
         touchemonstre = false;

         //fonction de frametime
         prevtime = currenttime;
         currenttime = SDL_GetTicks();
         deltatime = (currenttime - prevtime) /1000.f;

        frametime += deltatime;
        if(frametime >= 1.f) //toute les secondes
        {
            //PUT HERE
            frametime = 0;
        }



        while(SDL_PollEvent(&events)){

            if(events.type == SDL_QUIT) display = false;

            if(events.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&xMouse, &yMouse);

            }
            if(events.type == SDL_MOUSEBUTTONDOWN)
            {
                cout<<xMouse<<" "<<yMouse<<endl;
                for(unsigned int i=0; i<game.defenses.size(); i++)
                {
                    int Defy = i/25; //transforme la position en i
                    int Defx = i%25; //transforme la position en j
                    //si on enfonce le bouton gauche de la souris et que la souris se trouve dans l'une des cases 
                    if(xMouse > Defx*37+40 && xMouse < Defx*37+40 + 35 &&  yMouse > Defy*37+122 && yMouse < Defy*37+122 +35)
                    { 
                        if(events.button.button == SDL_BUTTON_LEFT && game.defenses[i].getType() == RIEN)
                        {
                            cout<<"Case :"<<i<<" enfoncé"<<endl; 
                              
                            AfficherMenuChoixShopBool = true; //Affiche le menu buy
                            AfficherMenuChoixUpgSellBool = false;
                            CaseChoisie = i;
                        }
                        else if(game.defenses[i].getType() != RIEN)
                        {
                            cout<<"Case :"<<i<<" enfoncé"<<endl; 

                            AfficherMenuChoixUpgSellBool = true;
                            AfficherMenuChoixShopBool = false;
                            AfficherMenuChoixBuyDefBool = false;

                            CaseChoisie = i;
                        }

                    }
                    if(AfficherMenuChoixShopBool == true)
                    {
                        if(xMouse > ParamInitShop[0] && xMouse < ParamInitShop[0]+ParamInitShop[2] &&  yMouse > ParamInitShop[1] && yMouse < ParamInitShop[1]+ParamInitShop[3])
                        {
                            AfficherMenuChoixShopBool = false;
                            AfficherMenuChoixBuyDefBool = true;
                        }
                    }
                    if(AfficherMenuChoixBuyDefBool == true)
                    {
                        if(xMouse > ParamInitShopCANON[0] && xMouse < ParamInitShopCANON[0] + ParamInitShopCANON[2] && yMouse > ParamInitShopCANON[1] && yMouse < ParamInitShopCANON[1] + ParamInitShopCANON[3])
                        {
                            retour = game.buyDefense(CANON, CaseChoisie);
                            AfficherMenuChoixBuyDefBool = false;
                        }
                        else if(xMouse > ParamInitShopDOUBLECANON[0] && xMouse < ParamInitShopDOUBLECANON[0] + ParamInitShopDOUBLECANON[2] && yMouse > ParamInitShopDOUBLECANON[1] && yMouse < ParamInitShopDOUBLECANON[1] + ParamInitShopDOUBLECANON[3])
                        {
                            retour = game.buyDefense(DOUBLECANON, CaseChoisie);
                            AfficherMenuChoixBuyDefBool = false;
                        }
                        else if(xMouse > ParamInitShopMORTIER[0] && xMouse < ParamInitShopMORTIER[0] + ParamInitShopMORTIER[2] && yMouse > ParamInitShopMORTIER[1] && yMouse < ParamInitShopMORTIER[1] + ParamInitShopMORTIER[3])
                        {
                            retour = game.buyDefense(MORTIER, CaseChoisie);
                            AfficherMenuChoixBuyDefBool = false;
                        }
                    }
                    if(AfficherMenuChoixUpgSellBool == true)
                    {
                        
                        if(xMouse > ParamInitSell[0] - 180 && xMouse < ParamInitSell[0] + ParamInitSell[2] && yMouse > ParamInitSell[1] && yMouse < ParamInitSell[1] + ParamInitSell[3])
                        {
                            retour = game.sellDefense(game.defenses[CaseChoisie]);
                            AfficherMenuChoixUpgSellBool = false;
                        }
                        if(xMouse > ParamInitUpgrade[0] && xMouse < ParamInitUpgrade[0] + ParamInitUpgrade[2] +240 && yMouse > ParamInitUpgrade[1] && yMouse < ParamInitUpgrade[1] + ParamInitUpgrade[3])
                        {
                            retour = game.upgradeDefense(game.defenses[CaseChoisie]);
                            AfficherMenuChoixUpgSellBool = false;
                        }

                    }
                }
                
            }

            //TEST Fonction event avec le clavier => si on est dans une case et qu'on appuie sur une des touches ca achète une défense
            if(events.type == SDL_KEYDOWN)
            {

                //Test fonction 
                if(events.key.keysym.sym == SDLK_SPACE)
                {
                    SDL_WaitEvent(&events);

                    lancervague = true;
                    //Pour l'instant touche space  mais imaginer un bouton "play" pour lancé la vague de monstre
                    SDL_WaitEvent(&events);//permet que l'action ne se realise pas 15 fois en même temps 
                    //TODO lancer la vagaue de monstre
                }
            }
        }

        /*  if(affichermsg) {
                    AfficherMessageErreur(retour);
                    SDL_WaitEvent(&events);
            }
         */
        
        if(lancervague != false){ //Lancer vague

            // On boucle sur les défenses
                for (unsigned int i=0; i < game.defenses.size(); i++) {
                    if (game.defenses[i].getType() == RIEN) continue; // Si la case est vide, on passe à la suivante
                    //cout<<"Tour de la défense : "<<i<<endl;

                    for (unsigned int a = 0; a < game.monstres.size(); a++) {
                        // Attack de la défense sur monstre a si possible
                        retour = game.DefHitMonstre(game.monstres[a], i, 1);
                        // Si la défense a touché le monstre
                        if (retour == 1) {
                            cout<<"Le monstre #"<<a<<" a été touché par la défense #"<<i<<endl;    
                            }
                        }
                    }
           // On boucle tout les monstres 
                    for (unsigned int i=0; i < game.monstres.size(); i++) {
                        game.monstres[i].setPosition(game.monstres[i].getPosition().x + 100*deltatime, 400); //en fonction du temps
             
                        // On regarde si le monstre atteint la base du joueur -> decremente nbVie joueur
                        if (game.monstres[i].getPosition().x >= DimWindowX) {
                            // On le supprime si c'est le cas
                            game.monstres.erase(game.monstres.begin()+i);

                            // Et on enlève une vie au joueur
                            game.joueur.setNbVies(game.joueur.getNbVies() - 1);
                        }

                        // On regarde si le monstre n'as plus de vies
                        if (game.monstres[i].getHp() < 1) {
                            // On le supprime si c'est le cas
                            game.monstres.erase(game.monstres.begin()+i);

                            // On ajoute un point au score joueur
                            game.joueur.setScore(game.joueur.getScore() + 1);

                            // On ajoute de l'argent au joueur
                            game.joueur.money += 100;
                            game.nbMonstreTues ++;
                        }

                        // On remet le tableau à la bonne taille
                        game.monstres.shrink_to_fit();

                        if(game.monstres.size() == 0) {
                            lancervague = false;
                            game.vague++;
                            game.InitVagueMonstre();    //Recréer une nouvelle vague de monstre
                        }
                    }
           
        }
        
        if(AfficherMenuChoixShopBool) 
        {
            AfficherMenuChoixShop();
            
            ostringstream Case;
            Case<<CaseChoisie;
            string CaseChoix("Case : " + Case.str());

            Couleur_Texte.r = 0; Couleur_Texte.g = 0; Couleur_Texte.b = 0;
            font_im.setSurface(TTF_RenderText_Solid(font,CaseChoix.c_str(),Couleur_Texte));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTexteInfosSelectedDef_Case;
            positionTexteInfosSelectedDef_Case.x = DimWindowX/2 - 45; positionTexteInfosSelectedDef_Case.y = 680; positionTexteInfosSelectedDef_Case.w = 90; positionTexteInfosSelectedDef_Case.h = 20;
            SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTexteInfosSelectedDef_Case);
        
        
        }    
        else if(AfficherMenuChoixBuyDefBool) AfficherMenuBuyDef();
        else if(AfficherMenuChoixUpgSellBool) 
        {
            AfficherMenuChoixUpgSell();
            AfficherInfosDefenseSelected(game.defenses[CaseChoisie],CaseChoisie, DimWindowX/2, 680, 100, 30 );
            
        }


        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
     
    }

}    
