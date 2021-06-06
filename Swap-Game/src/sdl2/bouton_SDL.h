#ifndef BOUTONSDL_H
#define BOUTONSDL_H

#include <SDL2/SDL.h>
#include <string>
using namespace std;


/**
* \brief gere les boutons sdl
*/
class Bouton {
private:
    /**
    * \brief la position du bouton sur la fenetre
    */
    SDL_Rect pos;

    /**
    * \brief le chemin d'acces a l'image de la texture
    */
    const char* imgPath;

    /**
    * \brief la position du nom du joueur
    */
    std::string op;

    /**
    * \brief les evenement appliques aux boutons
    */
    const SDL_Event* ptrEvents;

public:
    /**
    * \brief la texture du bouton
    */
    SDL_Texture* imgTexture;    // on met la texture en public pour pouvoir l'initialiser
                                //car le faire dans une fonction membre
                                //nécessite d'ajouter un membre renderer à la class

    /**
    * \brief la surface boutons
    */
   SDL_Surface* img;

   /**
   * \brief le constructeur par defaut du bouton
   */
    Bouton();

    /**
    * \brief defini la position du bouton
    */
    void setPos(const int x, const int y,const int w,const int h);
    /**
    * \brief définit le chemin de l'image et la charge sur la Surface
    */
    void setImg(const char* path);


    //void setOpStr(const char* opStr);
    //définit le string d'opération

    void setOpStr(std::string opStr);

    void setEvents(const SDL_Event & events);

    SDL_Rect getPos();

    const char* getImgPath();

    SDL_Surface* getImg();

    //const char* getOpStr();
    //retourne le string d'opération
    string getOpStr();


    int handle_events();
    //détecteur d'évenements souris
    //retourne 1 si on clique sur le bouton, 0 sinon
};


#endif
