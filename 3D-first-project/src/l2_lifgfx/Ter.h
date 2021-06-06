#ifndef TER_H
#define TER_H
#define _USE_MATH_DEFINES
#include "glcore.h"

#include "window.h"
#include "program.h"
#include "texture.h"
#include "mesh.h"
#include "draw.h"
#include "vec.h"
#include "mat.h"
#include "orbiter.h"
#include "app.h"


#include "AnimationCurve.h"
#include "pacman_core/Jeu.h"
    // pour dessiner du point de vue d'une camera

using namespace std;

/** \brief crée et modifie le terrain du monde
 *
 */


class Ter
{
    public:
            /** \brief donne la position du point recherché dans le tableau 1D
             *
             * \param i : la position x du point recherché
             * \param j : la position y du point recherché
             * \return la position du point recherché dans le tableau 1D
             *
             */
          int trouverPosition(int i,int j);

          /** \brief constructeur par default du terrain
           *
           * \param point de départ du terrain
           * \param point d'arriver du terrain
           * \param nombre de subdivision du terrain en x
           * \param nombre de subdivision du terrain en y
           */
          Ter(int Va[2],int Vb[2],int i, int j);

            /** \brief constructeur depuis une image du terrain
           *
           * \param image d'ou es lue le terrain (en niveau de gris)
           * \param hauteur minimale du terrain
           * \param hauteur maximale du terrain
           */
          Ter(Image I,float z1, float z2);

          /** \brief initialisateur du terrain (crée tout les triangles du terrain)
           *
           * \return le terrain ainsi créé
           *
           */
          Mesh creationM();

          /** \brief recupère le point rechercher à la bonne position dans le tableau
           *
           * \param position du point en x
           * \param position du point en y
           * \return le point à la postion i,j (largeur,hauteur,longueur)
           *
           */
          Point recupPoint(int i,int j);

          /** \brief trouve un point aléatoire sur le terrain
           *
           */
          void aleaSurD();

          /** \brief trouve un point aléatoire sur le terrain a partir d'une image
           *
           *  \param  l'image d'ou es lu le point;
           */
          void aleaSurD(Image img);

          /** \brief trouve la hauteur assocciée au point v1 et v2 sur une image
           * \param position du point en x
           * \param position du point en y
           * \param l'image d'ou est lu la hauteur
           * \return la hauteur moyenne au point (v1,v2);
           */
          float Elevation(float V1,float V2,Image img);

          /** \brief trouve la hauteur assocciée au point v1 et v2
           * \param position du point en x
           * \param position du point en y
           * \return la hauteur moyenne au point (v1,v2);
           */
          float Elevation(float V1,float V2);

          /** \brief trouve la coordonnée x du point d
           *
           * \param  dire si on veut la coordonnée en x ou en y
           * \return la coordonnée i du point d (0 ou 1)
           *
           */
          float getd2(int i);

          /** \brief trouve le nombre de subdivision en x du terrain
           *
           * \return le nombre de subdivision en x du terrain
           *
           */
          int getnx();

          /** \brief trouve le nombre de subdivision en y du terrain
           *
           * \return le nombre de subdivision en y du terrain
           *
           */
          int getny();
    protected:

            /** \brief point renvoyé par la fonction aleaSurD
             *
             */
          float d[2];

          /** \brief point de depart du terrain
            *
            */
          int a[2];

          /** \brief point final du terrain
            *
            */
          int b[2];

          /** \brief nombre de subdivision en x
             *
             */
          int nx;

          /** \brief nombre de subdivision en x
             *
             */
          int ny;

          /** \brief tableau des hauteurs de mon terrain
             *
             */
          std::vector<float> z;


    private:
};

#endif
