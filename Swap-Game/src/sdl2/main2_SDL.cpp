#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>

#include "affichage_SDL.h"


using namespace std;

int main() {

    affichageSDL aff;

    aff.initSDL();
    aff.initListes();
    aff.initBoutons();
    aff.initBoutonsMenus();
    aff.initBoutonsNiv();
    aff.initBoutonsVic();
    aff.initDeco();
    aff.boucleSDL();
    aff.detruitSDL();


    return 0;
}
