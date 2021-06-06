#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <unistd.h>
#include "affichage_SDL.h"
#include "../main/client.h"
#include <time.h>
#include <ctime>



void affichageSDL::initSDL() {

    WINDIMX = 800;
    WINDIMY = 600;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
		 "Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDIMX, WINDIMY, SDL_WINDOW_SHOWN);
    if(window == 0) {
        cout << "Erreur lors de la creation de la window : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",100);
    if (font == NULL) {
            cout << "Failed to losad OpenSans.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
            SDL_Quit();
            exit(EXIT_FAILURE);
	}

	font_color.r = 250;font_color.g = 80;font_color.b = 13;

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);



}

SDL_Surface* affichageSDL::loadSurfaceFromImage ( std::string path )
{
  //imgPath = path.c_str();
    //The final optimized image
  SDL_Surface* loadedSurface = NULL;

    //Load image at specified path
    SDL_Surface* optimizedSurface = IMG_Load( path.c_str() );//SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
      std::cout<<"test1"<<std::endl;
        optimizedSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface( window )->format, NULL );
	std::cout<<"test2"<<std::endl;
        if( optimizedSurface == NULL )
        {
	  printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

SDL_Texture* affichageSDL::CreateTextureFromString(string txt) {
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, txt.c_str(), font_color);
    return SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void affichageSDL::initListes() {

    tdA.ajouterElement(1);
    tdA.ajouterElement(2);
    tdA.ajouterElement(3);
    tdA.ajouterElement(4);
    posListeA.x=0.25*WINDIMX;
    posListeA.y=0.2*WINDIMY;
    posListeA.w=40*tdA.taille_utilisee;
    posListeA.h=100;

    tdB.ajouterElement(1);
    tdB.ajouterElement(0);
    tdB.ajouterElement(0);
    tdB.ajouterElement(0);
    posListeB.x=0.25*WINDIMX;
    posListeB.y=0.5*WINDIMY;
    posListeB.w=40*tdB.taille_utilisee;
    posListeB.h=100;

    textureListeA = CreateTextureFromString(tdA.TDtoString());
    textureListeB = CreateTextureFromString(tdB.TDtoString());

    /*listeA = TTF_RenderText_Solid(font,tdA.TDtoString().c_str(),font_color);
    listeB = TTF_RenderText_Solid(font,tdB.TDtoString().c_str(),font_color);

    std::cout << "tda: " << tdA.TDtoString() << std::endl << "tdb :" << tdB.TDtoString() << std::endl;

    textureListeA = SDL_CreateTextureFromSurface(renderer, listeA);
    textureListeB = SDL_CreateTextureFromSurface(renderer, listeB);
    */
}


void affichageSDL::initBoutons() {
    string file;
    ifstream work("./data/nomaction"); //on attribue a chaque bouton le nom de sa fonction grace a ce fichier
    for (int i=0;  i <=10; i++) {
        file="./data/sprites/buttons/mouse_out/fct";
        file+=to_string(i+1);
        file+=".png";
        std::cout << file << std::endl;
        tabBouton[i].setEvents(events);
        tabBouton[i].setPos((WINDIMX/11)*i+20, 0.9*WINDIMY,50,50);
        tabBouton[i].img=loadSurfaceFromImage(file);
        tabBouton[i].imgTexture = SDL_CreateTextureFromSurface(renderer, tabBouton[i].getImg());
        if(work.is_open()) {
            work >> file;
            std::cout << file << std::endl;
            tabBouton[i].setOpStr(file.c_str());
        }
    }
    work.close();
}

void affichageSDL::initBoutonsMenus() {
    string file;
    ifstream work("./data/nomactionmenus"); //on attribue a chaque bouton le nom de sa fonction grace a ce fichier
    for (int i=0;  i <=3; i++) {
        file="./data/sprites/buttons/mouse_out/menus";
        file+=to_string(i+1);
        file+=".png";
        std::cout << file << std::endl;
        tabBoutonMenus[i].setEvents(events);
        tabBoutonMenus[i].setPos(WINDIMX/2-150, WINDIMY/18*(3*i+5),300,70);;
        if(i==3)
        {
          tabBoutonMenus[i].setPos(0.9*WINDIMX, 0.85*WINDIMY,70,70);
        }
        tabBoutonMenus[i].img=loadSurfaceFromImage(file);
        tabBoutonMenus[i].imgTexture = SDL_CreateTextureFromSurface(renderer, tabBoutonMenus[i].getImg());
        if(work.is_open()) {
            work >> file;
            std::cout << file << std::endl;
            tabBoutonMenus[i].setOpStr(file.c_str());
        }
    }
    work.close();
}

void affichageSDL::initBoutonsNiv() {
    string file;
    ifstream work("./data/nomactionniv"); //on attribue a chaque bouton le nom de sa fonction grace a ce fichier
    for (int i=0;  i <=4; i++) {
        file="./data/sprites/buttons/mouse_out/niveau";
        file+=to_string(i+1);
        file+=".png";
        std::cout << file << std::endl;
        tabBoutonNiv[i].setEvents(events);
        tabBoutonNiv[i].setPos((WINDIMX/2-150), 50+50*(i+1),200,50);
        if(i==4)
        {
          tabBoutonNiv[i].setPos(0.1*WINDIMX, 0.1*WINDIMY,50,50);
        }
        tabBoutonNiv[i].img=loadSurfaceFromImage(file);
        tabBoutonNiv[i].imgTexture = SDL_CreateTextureFromSurface(renderer, tabBoutonNiv[i].getImg());
        if(work.is_open()) {
            work >> file;
            std::cout << file << std::endl;
            tabBoutonNiv[i].setOpStr(file.c_str());
        }
    }
    work.close();
}
void affichageSDL::initBoutonsVic() {
    string file;
    ifstream work("./data/nomactionvic"); //on attribue a chaque bouton le nom de sa fonction grace a ce fichier
    for (int i=0;  i <=2; i++) {
        file="./data/sprites/buttons/mouse_out/vic";
        file+=to_string(i+1);
        file+=".png";
        std::cout << file << std::endl;
        tabBoutonVic[i].setEvents(events);
        tabBoutonVic[i].setPos((WINDIMX/2-150), 100+80*(i+1),200,70);
        tabBoutonVic[i].img=loadSurfaceFromImage(file);
        tabBoutonVic[i].imgTexture = SDL_CreateTextureFromSurface(renderer, tabBoutonVic[i].getImg());
        if(work.is_open()) {
            work >> file;
            std::cout << file << std::endl;
            tabBoutonVic[i].setOpStr(file.c_str());
        }
    }
    work.close();
}

void affichageSDL::initDeco(){
  string A = "A |";
  string B = "B |";
  string barre = "_______";

  PositionDeco[0].x=0.10*WINDIMX;
  PositionDeco[0].y=0.2*WINDIMY;
  PositionDeco[0].h=100;
  PositionDeco[0].w=70;

  PositionDeco[1].x=0.10*WINDIMX;
  PositionDeco[1].y=0.5*WINDIMY;
  PositionDeco[1].h=100;
  PositionDeco[1].w=70;

  PositionDeco[2].x=0.10*WINDIMX;
  PositionDeco[2].y=0.4*WINDIMY;
  PositionDeco[2].h=20;
  PositionDeco[2].w=640;

  Positionvie.x=(WINDIMX)*0.8;
  Positionvie.y=(WINDIMY)*0.05;
  Positionvie.w=100;
  Positionvie.h=50;
  Positionchrono.x=(WINDIMX)*0.3;
  Positionchrono.y=(WINDIMY)*0.05;
  Positionchrono.w=250;
  Positionchrono.h=70;
  PositionTexte.x=(WINDIMX)*0.3;
  PositionTexte.y=(WINDIMY)*0.2;
  PositionTexte.w=250;
  PositionTexte.h=20;
  PositionNom.x=(WINDIMX)*0.02;
  PositionNom.y=(WINDIMY)*0.6;
  PositionNom.w=500;
  PositionNom.h=60;

  textureAccueil=CreateTextureFromString("bienvenue sur notre jeu, en esperant qu'il vous amuse");
  PositionAccueil.x=80;
  PositionAccueil.y=200;
  PositionAccueil.w=640;
  PositionAccueil.h=90;

  PositionScore.x=40;
  PositionScore.y=40;
  PositionScore.w=100;
  PositionScore.h=50;

  tabLogo.setPos((WINDIMX*0.25),WINDIMY*0.02 ,400,150);
  tabLogo.img=loadSurfaceFromImage("./data/logo.png");
  tabLogo.imgTexture = SDL_CreateTextureFromSurface(renderer, tabLogo.getImg());

  texturesDeco[0] = CreateTextureFromString(A);
  texturesDeco[1] = CreateTextureFromString(B);
  texturesDeco[2] = CreateTextureFromString(barre);

}



void affichageSDL::updateListes(const std::string& op,niveau niveau1,int & m) {
  if(niveau1.getFonctionActivee(0))
  {
    if(op=="sa")
    {
      niveau1.sa(tdA);
      m++;
    }
  }
  if(niveau1.getFonctionActivee(1))
  {
    if(op=="sb")
    {
      niveau1.sa(tdB);
      m++;
    }
  }
  if(niveau1.getFonctionActivee(2))
  {
    if(op=="ss")
    {
      niveau1.ss(tdA,tdB);
      m++;
    }
  }
  if(niveau1.getFonctionActivee(3))
  {
    if(op=="pb")
    {
      niveau1.pa(tdA,tdB);
      posListeB.w=40*tdB.taille_utilisee;
      posListeA.w=40*tdA.taille_utilisee;
      m++;
    }
  }
  if(niveau1.getFonctionActivee(4))
  {
    if(op=="pa")
    {
      niveau1.pa(tdB,tdA);
      posListeB.w=40*tdB.taille_utilisee;
      posListeA.w=40*tdA.taille_utilisee;
      m++;
    }
  }
  if(niveau1.getFonctionActivee(5))
  {
    if(op=="ra")
    {
      niveau1.ra(tdA);
      m++;
    }
  }
  if(niveau1.getFonctionActivee(6))
  {
    if(op=="rb")
    {
      niveau1.ra(tdB);
      m++;
    }
  }
  if(niveau1.getFonctionActivee(7))
  {
    if(op=="rr")
    {
      niveau1.rr(tdA,tdB);
      m++;
    }
  }
  if(niveau1.getFonctionActivee(8))
  {
    if(op=="rra")
    {
      niveau1.rra(tdA);
      m++;
    }
  }
  if(niveau1.getFonctionActivee(9))
  {
    if(op=="rrb")
    {
      niveau1.rra(tdB);
      m++;
    }
  }
  if(niveau1.getFonctionActivee(10))
  {
    if(op=="rrr")
    {
      niveau1.rrr(tdA,tdB);
      m++;
    }
  }
    textureListeA = CreateTextureFromString (tdA.TDtoString());
    textureListeB = CreateTextureFromString (tdB.TDtoString());
}

void affichageSDL::updateListesMenus(const std::string& op, int &choi, jeu &jeu1, niveau &niveau1,int &niveauEC) {
  if(op=="normal")
  {
      choi=1;
  }
  if(op=="endless")
  {
      choi=5;
  }
  if(op=="multi")
  {
      choi=9;
  }
  if(op=="leaderboard")
  {
      choi=7;
  }
  if(op=="niveau1")
  {
      niveauEC=0;
      TableauDynamique *tabB;
      TableauDynamique *tabA;
      tabA=jeu1.Getniveau(0).getListe();
      tabB=jeu1.Getniveau(0).getListeTransfert();
      tdA.vider();
      tdB.vider();
      for(int i=0;i<tabA->taille_utilisee;i++)
      {
        tdA.ajouterElement(tabA->valeurIemeElement(i));
      }
      posListeB.w=40*tdB.taille_utilisee;
      posListeA.w=40*tdA.taille_utilisee;
      textureListeA = CreateTextureFromString(tdA.TDtoString());
      textureListeB = CreateTextureFromString(tdB.TDtoString());
      niveau1=jeu1.Getniveau(0);
      choi=2;
  }
  if(op=="niveau2")
  {
    niveauEC=1;
    TableauDynamique *tabB;
    TableauDynamique *tabA;
    tabA=jeu1.Getniveau(1).getListe();
    tabB=jeu1.Getniveau(1).getListeTransfert();
    tdA.vider();
    tdB.vider();
    for(int i=0;i<tabA->taille_utilisee;i++)
    {
      tdA.ajouterElement(tabA->valeurIemeElement(i));
    }
    posListeB.w=40*tdB.taille_utilisee;
    posListeA.w=40*tdA.taille_utilisee;
    textureListeA = CreateTextureFromString(tdA.TDtoString());
    textureListeB = CreateTextureFromString(tdB.TDtoString());
    niveau1=jeu1.Getniveau(1);
    choi=2;
  }
  if(op=="niveau3")
  {
    niveauEC=2;
    TableauDynamique *tabB;
    TableauDynamique *tabA;
    tabA=jeu1.Getniveau(2).getListe();
    tabB=jeu1.Getniveau(2).getListeTransfert();
    tdA.vider();
    tdB.vider();
    for(int i=0;i<tabA->taille_utilisee;i++)
    {
      tdA.ajouterElement(tabA->valeurIemeElement(i));
    }
    posListeB.w=40*tdB.taille_utilisee;
    posListeA.w=40*tdA.taille_utilisee;
    textureListeA = CreateTextureFromString(tdA.TDtoString());
    textureListeB = CreateTextureFromString(tdB.TDtoString());
    niveau1=jeu1.Getniveau(2);
    choi=2;
  }
  if(op=="niveau4")
  {
      niveauEC=3;
      TableauDynamique *tabB;
      TableauDynamique *tabA;
      tabA=jeu1.Getniveau(3).getListe();
      tabB=jeu1.Getniveau(3).getListeTransfert();
      tdA.vider();
      tdB.vider();
      for(int i=0;i<tabA->taille_utilisee;i++)
      {
        tdA.ajouterElement(tabA->valeurIemeElement(i));
      }
      posListeB.w=40*tdB.taille_utilisee;
      posListeA.w=40*tdA.taille_utilisee;
      textureListeA = CreateTextureFromString(tdA.TDtoString());
      textureListeB = CreateTextureFromString(tdB.TDtoString());
      niveau1=jeu1.Getniveau(3);
      choi=2;
  }
  if(op=="retour")
  {
    choi=0;
    score=0;
    multi=1;
  }
  if(op=="menus")
  {
    choi=1;
  }
  if(op=="rejouer")
  {
    TableauDynamique *tabB;
    TableauDynamique *tabA;
    tabA=jeu1.Getniveau(niveauEC).getListe();
    tabB=jeu1.Getniveau(niveauEC).getListeTransfert();
    tdA.vider();
    tdB.vider();
    for(int i=0;i<tabA->taille_utilisee;i++)
    {
      tdA.ajouterElement(tabA->valeurIemeElement(i));
    }
    textureListeA = CreateTextureFromString(tdA.TDtoString());
    textureListeB = CreateTextureFromString(tdB.TDtoString());
    niveau1=jeu1.Getniveau(1);
    choi=2;
  }
  if(op=="nextlvl" && niveauEC<=3)
  {
    niveauEC++;
    TableauDynamique *tabB;
    TableauDynamique *tabA;
    tabA=jeu1.Getniveau(niveauEC).getListe();
    tabB=jeu1.Getniveau(niveauEC).getListeTransfert();
    tdA.vider();
    tdB.vider();
    for(int i=0;i<tabA->taille_utilisee;i++)
    {
      tdA.ajouterElement(tabA->valeurIemeElement(i));
    }
    textureListeA = CreateTextureFromString(tdA.TDtoString());
    textureListeB = CreateTextureFromString(tdB.TDtoString());
    niveau1=jeu1.Getniveau(niveauEC);
    choi=2;
  }
}


void affichageSDL::detruitSDL() {

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(textureListeA);
    SDL_DestroyTexture(textureListeB);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void affichageSDL::boucleSDL() {
  int choix=8;
  int travail=1;
  jeu jeu1;
  jeu1.InitJeu();
  niveau niveau1;
  int niveauEC;
  int niveauEnd=3;
  bool timer=1;
  bool endlessInit=1;
  int nblvlPass=0;
  int tailleEnd=4;
  time_t timed;
  struct tm * tmtime;
	while(!terminer) {
        SDL_WaitEvent(&events);
        if(events.window.event == SDL_WINDOWEVENT_CLOSE
                    || events.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
          {
            jeu1.SaveJeu();
            terminer = true;
          }
        SDL_RenderClear(renderer);
        if(choix==0)
        {
          for (int i = 0; i <= 3; i++) {
              int op = tabBoutonMenus[i].handle_events();
              std::string currentOp = tabBoutonMenus[i].getOpStr();
              if(op!=0){
                  updateListesMenus(currentOp,choix,jeu1,niveau1,niveauEC);
              }

              SDL_Rect temp = tabBoutonMenus[i].getPos();
              //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
              //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
              SDL_RenderCopy(renderer, tabBoutonMenus[i].imgTexture, NULL, &temp);
              /* il est nécessaire de prendre un pointeur sur un SDL_Rect pour la fonction
               * SDL_RenderCopy, cependant il est impossible de prendre directement l'adresse
               * d'un membre d'une classe en c++. Donc on utilise une variable intermédiaire */
          }
          SDL_Rect temp = tabLogo.getPos();
          SDL_RenderCopy(renderer, tabLogo.imgTexture, NULL, &temp);
        }
        if (choix==1)
        {

          for (int i = 0; i <= 3; i++) {
              string test="";
              if(jeu1.Getniveau(i).getNbEtoilePourDebloquer()<=jeu1.GettotalEtoile())
              {
                if(jeu1.Getniveau(i).getReussi()==1)
                {
                    test+="reussi avec ";
                    test+=jeu1.Getniveau(i).getEtoile()+48;
                    test+=" etoiles";
                    textureTextNiveau[i]=CreateTextureFromString(test);
                    Positiontext[i].x=WINDIMX/2+55;
                    Positiontext[i].y=50+50*(i+1);
                    Positiontext[i].w=200;
                    Positiontext[i].h=50;
                    SDL_RenderCopy(renderer, textureTextNiveau[i], NULL, &Positiontext[i]);
                }
              int op = tabBoutonNiv[i].handle_events();
              std::string currentOp = tabBoutonNiv[i].getOpStr();
              if(op!=0){
                  updateListesMenus(currentOp,choix,jeu1,niveau1,niveauEC);
              }

              SDL_Rect temp = tabBoutonNiv[i].getPos();
              //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
              //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
              SDL_RenderCopy(renderer, tabBoutonNiv[i].imgTexture, NULL, &temp);
            }
              /* il est nécessaire de prendre un pointeur sur un SDL_Rect pour la fonction
               * SDL_RenderCopy, cependant il est impossible de prendre directement l'adresse
               * d'un membre d'une classe en c++. Donc on utilise une variable intermédiaire */
          }
          int op = tabBoutonNiv[4].handle_events();
          std::string currentOp = tabBoutonNiv[4].getOpStr();
          if(op!=0){
              updateListesMenus(currentOp,choix,jeu1,niveau1,niveauEC);
          }

          SDL_Rect temp = tabBoutonNiv[4].getPos();
          //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
          //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
          SDL_RenderCopy(renderer, tabBoutonNiv[4].imgTexture, NULL, &temp);
        }
        if (choix==2)
        {
          if(timer==1)
          {
            time(&timed);
            tmtime=localtime(&timed);
            tmtime->tm_min=tmtime->tm_min+1;
            timer=0;
          }
          if(jeu1.verifOrdre(tdA) && tdB.taille_utilisee==0)
          {
              #ifdef _WIN32
              Sleep(1000);
              #else
              sleep(1);
              #endif
              choix=3;
          }
          string chrono="timer : ";
          if(niveauEC!=4)
          {
              chrono+=to_string(jeu1.modifChronograph(*tmtime));
              if(jeu1.modifChronograph(*tmtime)<=0)
              {
                  #ifdef _WIN32
                  Sleep(1000);
                  #else
                  sleep(1);
                  #endif
                  choix=4;
              }
          }
          else
          {
              chrono += "bloque";
          }
          for (int i = 0; i <= 10; i++) {
              int op = tabBouton[i].handle_events();
              std::string currentOp = tabBouton[i].getOpStr();
              if(op!=0){
                  updateListes(currentOp,niveau1,nbCoup);
              }

              SDL_Rect temp = tabBouton[i].getPos();
              //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
              //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
              if(jeu1.Getniveau(niveauEC).getFonctionActivee(i)==1)
              {
                SDL_RenderCopy(renderer, tabBouton[i].imgTexture, NULL, &temp);
              }
              /* il est nécessaire de prendre un pointeur sur un SDL_Rect pour la fonction
               * SDL_RenderCopy, cependant il est impossible de prendre directement l'adresse
               * d'un membre d'une classe en c++. Donc on utilise une variable intermédiaire */
          }
          for (int i = 0; i<3; i++)
       	    {
       	      SDL_RenderCopy(renderer, texturesDeco[i], NULL, &PositionDeco[i]);
       	    }
          SDL_RenderCopy(renderer, CreateTextureFromString(chrono), NULL, &Positionchrono);
          SDL_RenderCopy(renderer, textureListeA, NULL, &posListeA);
          SDL_RenderCopy(renderer, textureListeB, NULL, &posListeB);
        }
        if (choix==3)
        {
          timer=1;
          if (nbCoup!=0)
          {
            jeu1.setVp(niveauEC,nbCoup);
          }
          nbCoup=0;
          for (int i = 0; i <= 2; i++) {
              int op = tabBoutonVic[i].handle_events();
              std::string currentOp = tabBoutonVic[i].getOpStr();
              if(op!=0){
                  updateListesMenus(currentOp,choix,jeu1,niveau1,niveauEC);
              }

              SDL_Rect temp = tabBoutonVic[i].getPos();
              //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
              //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
              SDL_RenderCopy(renderer, tabBoutonVic[i].imgTexture, NULL, &temp);
              /* il est nécessaire de prendre un pointeur sur un SDL_Rect pour la fonction
               * SDL_RenderCopy, cependant il est impossible de prendre directement l'adresse
               * d'un membre d'une classe en c++. Donc on utilise une variable intermédiaire */
        }
      }
      if (choix==4)
      {
        timer=1;
        //nbCoup=0;
        for (int i = 0; i <= 1; i++) {
            int op = tabBoutonVic[i].handle_events();
            std::string currentOp = tabBoutonVic[i].getOpStr();
            if(op!=0){
                updateListesMenus(currentOp,choix,jeu1,niveau1,niveauEC);
            }

            SDL_Rect temp = tabBoutonVic[i].getPos();
            //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
            //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
            SDL_RenderCopy(renderer, tabBoutonVic[i].imgTexture, NULL, &temp);
            /* il est nécessaire de prendre un pointeur sur un SDL_Rect pour la fonction
             * SDL_RenderCopy, cependant il est impossible de prendre directement l'adresse
             * d'un membre d'une classe en c++. Donc on utilise une variable intermédiaire */
           }
      }
      if (choix==5)
      {
        if(niveauEnd==0)
        {
          choix=6;
        }
        if(endlessInit)
        {
          string vie= "vie : ";
          vie += niveauEnd+48;
          texturevie=CreateTextureFromString(vie);
          tdA.vider();
          tdB.vider();
          niveau1.getListe()->vider();
          niveau1.getListeTransfert()->vider();
          jeu1.aleatoireGen(niveau1,tailleEnd);
          cout<<"je suis la apres"<<endl;
          for(int i=0;i<niveau1.getListe()->taille_utilisee;i++)
          {
            tdA.ajouterElement(niveau1.getListe()->valeurIemeElement(i));
          }
          textureListeA = CreateTextureFromString(tdA.TDtoString());
          textureListeB = CreateTextureFromString(tdB.TDtoString());
          endlessInit=0;
        }
        if(timer==1)
        {
          time(&timed);
          tmtime=localtime(&timed);
          tmtime->tm_min=tmtime->tm_min+2;
          timer=0;
        }
        if(jeu1.verifOrdre(tdA) && tdB.taille_utilisee==0)
        {
            #ifdef _WIN32
            Sleep(1000);
            #else
            sleep(1);
            #endif
            timer=1;
            if(nbCoup !=0)
            {
              score+=((niveau1.getNbCoupMax())/nbCoup)*50;
            }
            else
            {
              score+=50;
            }
            if(tailleEnd<10)
            {
              tailleEnd++;
            }
            nblvlPass++;
            endlessInit=1;
        }
        string chrono="timer : ";
        if(niveauEC!=4)
        {
            chrono+=to_string(jeu1.modifChronograph(*tmtime));
            if(jeu1.modifChronograph(*tmtime)<=0)
            {
                #ifdef _WIN32
                Sleep(1000);
                #else
                sleep(1);
                #endif
                timer=1;
                if(tailleEnd>4)
                {
                  tailleEnd--;
                }
                niveauEnd=niveauEnd-1;
                endlessInit=1;
            }
        }
        else
        {
            chrono += "bloque";
        }
        SDL_RenderCopy(renderer, CreateTextureFromString(chrono), NULL, &Positionchrono);
        for (int i = 0; i <= 10; i++) {
            int op = tabBouton[i].handle_events();
            std::string currentOp = tabBouton[i].getOpStr();
            if(op!=0){
                updateListes(currentOp,niveau1,nbCoup);
            }

            SDL_Rect temp = tabBouton[i].getPos();
            //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
            //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
            SDL_RenderCopy(renderer, tabBouton[i].imgTexture, NULL, &temp);
            /* il est nécessaire de prendre un pointeur sur un SDL_Rect pour la fonction
             * SDL_RenderCopy, cependant il est impossible de prendre directement l'adresse
             * d'un membre d'une classe en c++. Donc on utilise une variable intermédiaire */
        }
         for (int i = 0; i<3; i++)
       	    {
       	      SDL_RenderCopy(renderer, texturesDeco[i], NULL, &PositionDeco[i]);
       	    }
        string texteS="score :";
        texteS+=to_string(score);
        SDL_RenderCopy(renderer, CreateTextureFromString(texteS), NULL, &PositionScore);
        SDL_RenderCopy(renderer, texturevie, NULL, &Positionvie);
        SDL_RenderCopy(renderer, textureListeA, NULL, &posListeA);
        SDL_RenderCopy(renderer, textureListeB, NULL, &posListeB);
      }
    if(choix==6)
    {
      string t="vous avez reussi";
      t += nblvlPass;
      t += "niveaux ! FELICITATION !";
      tailleEnd=4;
      int op = tabBoutonNiv[4].handle_events();
      std::string currentOp = tabBoutonNiv[4].getOpStr();
      if(op!=0){
          updateListesMenus(currentOp,choix,jeu1,niveau1,niveauEC);
      }

      SDL_Rect temp = tabBoutonNiv[4].getPos();
      //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
      //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
      for (int i = 0; i<3; i++)
   	    {
   	      SDL_RenderCopy(renderer, texturesDeco[i], NULL, &PositionDeco[i]);
   	    }
      SDL_RenderCopy(renderer, CreateTextureFromString(t), NULL, &PositionTexte);
      SDL_RenderCopy(renderer, tabBoutonNiv[4].imgTexture, NULL, &temp);
    }
    if(choix==7)
    {
      if(travail)
      {
        string t ="";
        t += nom;
        t += " ";
        t += "50";
        string s[10];
        string adresse="localhost";
        string port="8081";
        string recupPos;
        gere_client(adresse,port,t,s, recupPos,1, tdA,nbCoup);
        for(int i=0;i<10;i++)
        {
          string final="";
          final+=to_string(i+1);
          final+=" - ";
          s[i]=s[i].substr(0,s[i].find('\n'));
          final+=s[i];
          PositionLeader[i].x=(WINDIMX)*0.4;
          PositionLeader[i].y=(50)+40*i;
          PositionLeader[i].w=15*final.size();
          PositionLeader[i].h=(40);
          textureLeader[i]=CreateTextureFromString(final);
        }
        string affich="";
        recupPos=recupPos.substr(0,recupPos.find('\n'));
        affich+=recupPos;
        affich+=" - ";
        affich+=t;
        PositionLeader[10].x=(WINDIMX)*0.4;
        PositionLeader[10].y=(50)+40*11;
        PositionLeader[10].w=(15)*affich.size();
        PositionLeader[10].h=(40);
        textureLeader[10]=CreateTextureFromString(affich);
        travail=0;
      }
      for(int i=0;i<11;i++)
      {
        SDL_RenderCopy(renderer, textureLeader[i], NULL, &PositionLeader[i]);
      }
      int op = tabBoutonNiv[4].handle_events();
      std::string currentOp = tabBoutonNiv[4].getOpStr();
      if(op!=0){
          updateListesMenus(currentOp,choix,jeu1,niveau1,niveauEC);
      }

      SDL_Rect temp = tabBoutonNiv[4].getPos();
      //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
      //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
      SDL_RenderCopy(renderer, tabBoutonNiv[4].imgTexture, NULL, &temp);
    }
    if (choix==8)
    {
      string saisie=" choisissez votre nom : ";
      if(events.type==SDL_KEYDOWN)
      {
                switch(events.key.keysym.sym)
                {
                    case 'q':
                        nom += 'a';
                        break;
                    case 'a':
                        nom += 'q';
                        break;
                    case 'w':
                        nom += 'z';
                        break;
                    case 'e':
                        nom += 'e';
                        break;
                    case 'r':
                        nom += 'r';
                        break;
                    case 't':
                        nom += 't';
                        break;
                    case 'y':
                        nom += 'y';
                        break;
                    case 'u':
                        nom += 'u';
                        break;
                    case 'i':
                        nom += 'i';
                        break;
                    case 'o':
                        nom += 'o';
                        break;
                    case 'p':
                        nom += 'p';
                        break;
                    case 's':
                        nom += 's';
                        break;
                    case 'd':
                        nom += 'd';
                        break;
                    case 'f':
                        nom += 'f';
                        break;
                    case 'g':
                        nom += 'g';
                        break;
                    case 'h':
                        nom += 'h';
                        break;
                    case 'j':
                        nom += 'j';
                        break;
                    case 'k':
                        nom += 'k';
                        break;
                    case 'l':
                        nom += 'l';
                        break;
                    case ';':
                        nom += 'm';
                        break;
                    case 'z':
                        nom += 'w';
                        break;
                    case 'x':
                        nom += 'x';
                        break;
                    case 'c':
                        nom += 'c';
                        break;
                    case 'v':
                        nom += 'v';
                        break;
                    case 'b':
                        nom += 'b';
                        break;
                    case 'n':
                        nom += 'n';
                        break;
                    case SDLK_SPACE:
                        choix=0;
                        break;
                    case SDLK_BACKSPACE:
                    nom=nom.substr(0,nom.size()-1);
                        break;
            }
          }
          saisie += nom;
          PositionNom.w=15*saisie.size();
          textureNom=CreateTextureFromString(saisie);
          SDL_Rect temp = tabLogo.getPos();
          SDL_RenderCopy(renderer, tabLogo.imgTexture, NULL, &temp);
          SDL_RenderCopy(renderer, textureAccueil, NULL, &PositionAccueil);
          SDL_RenderCopy(renderer, textureNom, NULL, &PositionNom);
    }
    if (choix==9)
    {
      if(multi == 1)
      {
        string t ="";
        t += nom;
        t += " ";
        t += "50";
        string s[10];
        string adresse="localhost";
        string port="8081";
        string recupPos;
        tdA.vider();
        tdB.vider();
        gere_client(adresse,port,t,s, recupPos,0, tdA,nbCoup);
        textureListeA = CreateTextureFromString(tdA.TDtoString());
        textureListeB = CreateTextureFromString(tdB.TDtoString());
        multi=0;
      }
      if(multi== 0)
      {
        if(timer==1)
          {
            time(&timed);
            tmtime=localtime(&timed);
            tmtime->tm_min=tmtime->tm_min+1;
            timer=0;
          }
          if(jeu1.verifOrdre(tdA) && tdB.taille_utilisee==0)
          {
              #ifdef _WIN32
              Sleep(1000);
              #else
              sleep(1);
              #endif
              multi=2;
          }
          string chrono="timer : ";
              chrono+=to_string(jeu1.modifChronograph(*tmtime));
              if(jeu1.modifChronograph(*tmtime)<=0)
              {
                  #ifdef _WIN32
                  Sleep(1000);
                  #else
                  sleep(1);
                  #endif
                  nbCoup=9999;
                  multi=2;
              }
          for (int i = 0; i <= 10; i++) {
              int op = tabBouton[i].handle_events();
              std::string currentOp = tabBouton[i].getOpStr();
              if(op!=0){
                  updateListes(currentOp,jeu1.Getniveau(3),nbCoup);
              }

              SDL_Rect temp = tabBouton[i].getPos();
              //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
              //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
                SDL_RenderCopy(renderer, tabBouton[i].imgTexture, NULL, &temp);
              /* il est nécessaire de prendre un pointeur sur un SDL_Rect pour la fonction
               * SDL_RenderCopy, cependant il est impossible de prendre directement l'adresse
               * d'un membre d'une classe en c++. Donc on utilise une variable intermédiaire */
          }
          for (int i = 0; i<3; i++)
            {
              SDL_RenderCopy(renderer, texturesDeco[i], NULL, &PositionDeco[i]);
            }
          SDL_RenderCopy(renderer, CreateTextureFromString(chrono), NULL, &Positionchrono);
          SDL_RenderCopy(renderer, textureListeA, NULL, &posListeA);
          SDL_RenderCopy(renderer, textureListeB, NULL, &posListeB);
        }
        if(multi==2)
        {
          string t ="";
          t += nom;
          t += " ";
          t += "50";
          string s[10];
          string adresse="localhost";
          string port="8081";
          string recupPos;
          tdA.vider();
          tdB.vider();
          gere_client(adresse,port,t,s, recupPos,0, tdA,nbCoup);
          multi = 3;
        }
        if(multi==3)
        {
          string vic="";
          if(nbCoup==0)
          {
            vic+="PERDU!";
          }
          else
          {
            vic+="VICTOIRE!";
          }
          PositionDeco[2].h=100;
          SDL_RenderCopy(renderer, CreateTextureFromString(vic), NULL, &PositionDeco[2]);
          PositionDeco[2].h=20;
          int op = tabBoutonNiv[4].handle_events();
          std::string currentOp = tabBoutonNiv[4].getOpStr();
          if(op!=0){
              updateListesMenus(currentOp,choix,jeu1,niveau1,niveauEC);
          }

          SDL_Rect temp = tabBoutonNiv[4].getPos();
          //std::cout << i << " : " << std::endl << "x=" << tabBouton[i].getPos().x << "; y=" << tabBouton[i].getPos().y
          //                                    << "; w=" << tabBouton[i].getPos().w << "; h=" << tabBouton[i].getPos().h << std::endl;
          SDL_RenderCopy(renderer, tabBoutonNiv[4].imgTexture, NULL, &temp);
        }

    }
    SDL_RenderPresent(renderer);
  }
}
