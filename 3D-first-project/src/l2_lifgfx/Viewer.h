
#ifndef VIEWER_H
#define VIEWER_H


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
#include "Ter.h"

/** \brief initialise le monde et les objets qui le compose puis les affiches
 *
 */


class Viewer : public App
{
public:
    Viewer();

    //! Initialise tout : compile les shaders et construit le programme + les buffers + le vertex array.
    //! renvoie -1 en cas d'erreur.
    int init();

    //! La fonction d'affichage
    int render();

    //! Libere tout
    int quit();

    void help();

    int update( const float time, const float delta );

protected:


    /** \brief la camera qui nous permet de voir
    *
    */
    Orbiter m_camera;
    /** \brief les parametres d'affichage
    *
    */
    DrawParam gl;
    /** \brief les animations pour les objets mouvant
    *
    */
    AnimationCurve m_anim;
    bool mb_cullface;
    bool mb_wireframe;
    Transform Tplane;

    /** \brief un axe
    *
    */
    Mesh m_axe;
    /** \brief une grille
    *
    */
    Mesh m_grid;
    /** \brief un cubemap
    *
    */
    Mesh m_cube;
    /** \brief un cylindre
    *
    */
    Mesh m_cylindre;
    /** \brief un cone
    *
    */
    Mesh m_cone;
    /** \brief une pyramide
    *
    */
    Mesh m_pyramide;
    /** \brief un cube
    *
    */
    Mesh m_cube2;
    /** \brief une sphere
    *
    */
    Mesh m_sphere;
    /** \brief un objet non identifié
    *
    */
    Mesh m_sphere2;
    /** \brief un rectangle
    *
    */
    Mesh m_bilboard;
    /** \brief la coordonnée de depart de mon terrain
    *
    */
    int a[2];
    /** \brief la coordonnée d'arrivée de mon terrain
    *
    */
    int b[2];
    /** \brief le terrain
    *
    */
    Ter *terrain;
    /** \brief un tableau des coordoonées ou sont placé les arbres sur le terrain
    *
    */
    Point T[50];
    /** \brief la texture du cube
    *
    */
    GLuint m_cube_texture;
    /** \brief la texture du terrain
    *
    */
    GLuint texture;
    /** \brief la texture du tronc de l'arbre
    *
    */
    GLuint texture_t;
    /** \brief la texture des feuilles de l'arbre
    *
    */
    GLuint texture_f;
    /** \brief la texture de l'eau
    *
    */
    GLuint texture_e;
    /** \brief la texture du cubemap
    *
    */
    GLuint texture_cube;
    /** \brief la texture du bilboard
    *
    */
    GLuint texture_b;
    /** \brief le terrain de l'eau
    *
    */
    Ter *terrain2;
    /** \brief la  heightmap d'ou sont lu les informations de positions
    *
    */
    Image image;
    /** \brief le terrain généré
    *
    */
    Mesh test;





    bool b_draw_grid;
    bool b_draw_axe;
    bool b_draw_animation;
    /** \brief initialise un axe
    *
    */
    void init_axe();
    /** \brief initialise une grille
    *
    */
    void init_grid();
    /** \brief initialise le cubemap
     *\param L= longueur du cube
     *\param l= largeur du cube
     *\param h= hauteur du cube
    *
    */
    void init_cube(float L,float l,float h);
    void init_boule();
    /** \brief initialise la sphere
     *\param n= nombre de subdivision de la sphere 
     *\param r= rayon de la sphere
    *
    */
    void init_sphere(int n,float r);
    /** \brief initialise le cylindre
     *\param n= nombre de subdivision du cylindre
     *\param h= hauteur du cylindre
     *\param r= rayon du cylindre
    *
    */
    void init_cylindre(int n,float h,float r);
    /** \brief initialise le cone
     *\param n= nombre de subdivision du cone
     *\param h= hauteur du cone
     *\param r= rayon du cone
    *
    */
    void init_cone(int n,float h,float r);
    /** \brief initialise la forme indéterminée
     *\param n= nombre de subdivision de la forme indéterminé
     *\param r= rayon de la forme indéterminé
    *
    */
    void init_forme(int n,float r);
    //void init_pyramide();
    /** \brief initialise le bilboard
     *
     */
    void init_bilboard();
    /** \brief initialise le cube
     *\param L= longueur du cube
     *\param l= largeur du cube
     *\param h= hauteur du cube
    *
    */
    void init_cube2(float L,float l,float h);
     /** \brief un rectangle
     *
     */
    Mesh m_quad;
     /** \brief texture du rectangle
     *
     */
    GLuint m_quad_texture;
     /** \brief initialise le rectangle
     *
     */
    void init_quad();
     /** \brief transformation appliqué sur le rectangle
     *
     */
    Transform Tquad;
    Jeu m_pacman;       // pacman
    GLuint m_tex_mur;
    GLuint m_tex_pacman;
    GLuint m_tex_fantome;
    GLuint m_tex_pastille;
    
    /** \brief dessine le cylindre avec la texture et les transformations souhaitée
     *\param T= Transformation sur le cylindre
     *\param tex= texture du cylindre 
    *
    */
    void draw_cylindre(const Transform& T,unsigned int tex);
    void draw_axe(const Transform& T);
    /** \brief dessine le cubemap avec la texture et les transformations souhaitée
     *\param T= Transformation sur le cubemap
     *\param tex= texture du cubemap 
    *
    */
    void draw_cube(const Transform& T, unsigned int tex);
    /** \brief dessine le cube avec la texture et les transformations souhaitée
     *\param T= Transformation sur le cube
     *\param tex= texture du cube 
    *
    */
    void draw_cube2(const Transform& T, unsigned int tex);
    /** \brief dessine le cone avec la texture et les transformations souhaitée
     *\param T= Transformation sur le cone
     *\param tex= texture du cone 
    *
    */
    void draw_cone(const Transform& T, unsigned int tex);
    /** \brief dessine l'avion avec la texture et les transformations souhaitée
     *\param T= Transformation sur l'avion
     *\param tex= texture de l'avion
    *
    */
    void draw_avion(const Transform& T, unsigned int tex);
    void draw_pacman(const Transform& T);
    /** \brief dessine la sphere avec la texture et les transformations souhaitée
     *\param T= Transformation sur la sphere
     *\param tex= texture de la sphere
    *
    */
    void draw_sphere(const Transform& T, unsigned int tex);
    /** \brief dessine le terrain avec la texture et les transformations souhaitée
     *\param T= Transformation sur le terrain
     *\param tex= texture du terrain
    *
    */
    void draw_terrain(const Transform& T, unsigned int tex);
    /** \brief dessine le terrain d'eau avec la texture et les transformations souhaitée
     *\param T= Transformation sur le terrain d'eau
     *\param tex= texture du terrain d'eau
    *
    */
    void draw_terrain2(const Transform& T, unsigned int tex);
    /** \brief dessine l'arbre(composé d'un cylindre et d'un cone)  avec la texture et les transformations souhaitée
     *\param T= Transformation sur l'arbre
     *\param tex= texture de l'arbre
    *
    */
    void draw_arbre(const Transform& T, unsigned int tex);
      /** \brief dessine l'arbre(composé de bilboard)  avec la texture et les transformations souhaitée
     *\param T= Transformation sur l'arbre
     *\param tex= texture de l'arbre
    *
    */
    void draw_arbre2(const Transform& T, unsigned int tex);
    void manageCameraLight();
};



#endif
