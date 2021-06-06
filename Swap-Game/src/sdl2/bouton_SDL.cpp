#include "bouton_SDL.h"

#include <iostream>
#include <string.h>

using namespace std;

Bouton::Bouton() {
    pos.x = 0; pos.y = 0;
}

void Bouton::setPos(const int x, const int y,const int w,const int h) {
    pos.x=x; pos.y=y; pos.w=w; pos.h=h;

}

void Bouton::setImg(const char* path) {
    imgPath = path;

    img = SDL_LoadBMP(path);
}

void Bouton::setOpStr(string opStr) {
    op=opStr;
    std::cout << op << std::endl;
}

void Bouton::setEvents(const SDL_Event & events) {
    ptrEvents = &events;
}

SDL_Rect Bouton::getPos() {
    return pos;
}

const char* Bouton::getImgPath() {
    return imgPath;
}

SDL_Surface* Bouton::getImg() {
    return img;
}

string Bouton::getOpStr() {
    return op;
}

int Bouton:: handle_events() {
    int x = 0, y = 0;

  /*  if (ptrEvents->type == SDL_MOUSEMOTION) { //condition qui sert si on décide de mettre des images differentes pour mouseover/mouseout
        x = ptrEvents->motion.x;
        y = ptrEvents->motion.y;

        if ((x > pos.x) && (x < pos.x + pos.w) && (y > pos.y) && (y < pos.y + pos.h)) {
            //on set l'image sur le mouseover

        }
        else {
            //on set l'image sur le mouseout
            //std::cout << "mouseout " << op << std::endl;
        }
    }*/

    if (ptrEvents->type == SDL_MOUSEBUTTONDOWN) {
        if (ptrEvents->button.button == SDL_BUTTON_LEFT) {
            x = ptrEvents->button.x;
            y = ptrEvents->button.y;

            if ((x > pos.x) && (x < pos.x + pos.w) && (y > pos.y) && (y < pos.y + pos.h)) {
                //on set l'image sur mousedown
                std::cout << "mousedown " << op << std::endl;
                return 1;
            }
        }
    }

  /*  if (ptrEvents->type == SDL_MOUSEBUTTONUP) {
        if (ptrEvents->button.button == SDL_BUTTON_LEFT) {
            x = ptrEvents->button.x;
            y = ptrEvents->button.y;

            if ((x > pos.x) && (x < pos.x + pos.w) && (y > pos.y) && (y < pos.y + pos.h)) {
                //on set l'image sur mouseup
                std::cout << "mouseup " << op << std::endl;
            }
        }
    }*/

    return 0;
}
