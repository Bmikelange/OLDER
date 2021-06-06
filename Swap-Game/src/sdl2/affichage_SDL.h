#ifndef AFFICHAGESDL_H
#define AFFICHAGESDL_H


#include "../main/jeu.h"
#include "bouton_SDL.h"


using namespace std;

/**
* \brief gere l'affichage dans une fenetre sdl
*/
class affichageSDL {
private :
    /**
    * \brief les dimensions de la fenetre d'affichage
    */
    int WINDIMX,WINDIMY;
    /**
    * \brief la fenetre sdl
    */
    SDL_Window* window = NULL;
//     SDL_Surface* listeA = NULL;
//     SDL_Surface* listeB = NULL;
    /**
    * \brief la liste des boutons en jeu
    */
    Bouton tabBouton [11];
    /**
    * \brief la liste des boutons du menus
    */
    Bouton tabBoutonMenus[4];
    /**
    * \brief la liste des boutons de selection du niveau
    */
    Bouton tabBoutonNiv[5];
    Bouton tabLogo;
    /**
    * \brief la liste des boutons en cas de victoires ou de defaite
    */
    Bouton tabBoutonVic[3];
    /**
    * \brief la position de nos liste sur la fenetre
    */
    SDL_Rect posListeA, posListeB;

    /**
    * \brief la texture de notre premiere liste
    */
    SDL_Texture* textureListeA = NULL;

    SDL_Texture* textureAccueil = NULL;
    /**
    * \brief la texture de la deuxieme liste
    */
    SDL_Texture* textureListeB = NULL;
    /**
    * \brief la liste des texture des boutons de menus
    */
    SDL_Texture* textureTextNiveau[4];
    /**
    * \brief la texture de la vie du joueur
    */
    SDL_Texture* texturevie = NULL;
    /**
    * \brief la liste des texture des boutons de jeu
    */
    SDL_Texture* textureLeader[11];
    /**
    * \brief la texture du nom du joueur
    */
    SDL_Texture* textureNom = NULL;
    /**
    * \brief la liste des texture des objets de decoration
    */
    SDL_Texture* texturesDeco[3];
    /**
    * \brief le nombre de coups fait sur une liste
    */
    int nbCoup=0;
    int score =0;
    int multi = 1;

    /**
    * \brief la position du text affichant le nombre d'etoile obtenu
    */
    SDL_Rect Positiontext[4];
    /**
    * \brief la position de la vie du joueur
    */
    SDL_Rect Positionvie;
    SDL_Rect PositionScore;
    SDL_Rect PositionAccueil;
    /**
    * \brief la position du nom du joueur
    */
    SDL_Rect PositionNom;
    /**
    * \brief la position du chronometre
    */
    SDL_Rect Positionchrono;
    /**
    * \brief la position de la selection de texte
    */
    SDL_Rect PositionTexte;
    /**
    * \brief la position du leader board
    */
    SDL_Rect PositionLeader[11];
    /**
    * \brief la position des decorations
    */
    SDL_Rect PositionDeco[3];
    /**
    * \brief le rendu de l'ecran
    */
    SDL_Renderer* renderer;
    /**
    * \brief la gestion du texte sur la sdl
    */
    TTF_Font* font;
    /**
    * \brief la couleur du font de la fenetre
    */
    SDL_Color font_color;
    /**
    * \brief les evenements gere par la sdl
    */
    SDL_Event events;

    /**
    * \brief la condition d'arret de la boucle de jeu
    */
    bool terminer = false;
    /**
    * \brief le nom du joueur
    */
    string nom="";

    /**
    * \brief les listes sur lesquelles le joueur joue
    */
    TableauDynamique tdA, tdB;

public :

    /**
    * \brief initialise la fenetre d'affichage
    */
    void initSDL();

    /**
    * \brief initialise les listes de jeu
    */
    void initListes();

    /**
    * \brief initialise les boutons de jeu
    */
    void initBoutons();

    /**
    * \brief initialise les boutons du menu principal
    */
    void initBoutonsMenus();

    /**
    * \brief initialise les boutons de selection des niveaux
    */
    void initBoutonsNiv();

    /**
    * \brief initialise les boutons de gestion de la victoire
    */
    void initBoutonsVic();

    /**
    * \brief initialise divers elements de decoration
    */
    void initDeco();

    /**
    * \brief cree une surface sdl a partir d'une image
    * \param path chemin d'acces a l'image
    * \return la surface sdl cree
    */
    SDL_Surface* loadSurfaceFromImage (std::string path);

    /**
    * \brief cree une texture sdl aexture a partir d'un string
    * \param txt le string a traiter
    * \return la texture cree
    */

    SDL_Texture* CreateTextureFromString(string txt);

    /**
    * \brief mofifie la liste en fonction du bouton appuye
    * \param op l'operation a effectue
    * \param niveau1 le niveau sur lequel on joue
    * \param m le nombre de coup
    */
    void updateListes(const std::string& op,niveau niveau1,int &m);

    /**
    * \brief action du menu en fonction du bouton appuye
    * \param op l'operation a effectue
    * \param choix l'ecran a afficher
    * \param jeu1 la partie sur laquelle le joueur joue
    * \param niveau1 le niveau sur lequel le joueur joue
    * \param niveauEC l'indice du niveau sur lequel le joueur joue
    */
    void updateListesMenus(const std::string& op, int &choix,jeu &jeu1, niveau &niveau1,int &niveauEC);

    /**
    * \brief la boucle de jeu separee en 9 cas possibles
    */
    void boucleSDL();

    /**
    * \brief detruit l'affichage sdl
    */
    void detruitSDL();

};


#endif
