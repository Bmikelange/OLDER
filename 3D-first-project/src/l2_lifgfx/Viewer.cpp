#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer.h"
#include "Ter.h"

using namespace std;


Viewer::Viewer() : App(1024, 768), mb_cullface(true), mb_wireframe(false), b_draw_grid(true), b_draw_axe(true), b_draw_animation(false)
{
    float n,m,j;
    image= read_image(smart_path("/data/terrain/terrain.png"));
    //if(image == Image::error())
        //cout<<"erreur de chargement"<<endl;
       //exit(0);
       int a[2];
       a[0]=-10;
       a[1]=-10;
       int b[2];
       b[0]=11;
       b[1]=10;
    terrain = new Ter(image,20.0,20.0);
    terrain2 = new Ter(a,b,21,20);
    for(int i=0;i<20;i++)
    {
      terrain->aleaSurD();
      n=terrain->getd2(0);
      m=terrain->getd2(1);
      j=terrain->Elevation(terrain->getd2(1),terrain->getd2(0));
      T[i]={n,j,m};
    }
}
void Viewer::help()
{
    printf("HELP:\n");
    printf("\th: help\n");
    printf("\tc: (des)active GL_CULL_FACE\n");
    printf("\tw: (des)active wireframe\n");
    printf("\ta: (des)active l'affichage de l'axe\n");
    printf("\tg: (des)active l'affichage de la grille\n");
    printf("\tz: (des)active l'affichage de la courbe d'animation\n");
    printf("\tfleches/pageUp/pageDown: bouge la camera\n");
    printf("\tCtrl+fleche/pageUp/pageDown: bouge la source de lumiere\n");
    printf("\tSouris+bouton gauche: rotation\n");
    printf("\tSouris mouvement vertical+bouton droit: (de)zoom\n");
}

int Viewer::init()
{
    cout<<"==>l2_lifgfx/Viewer"<<endl;
    // etat par defaut openGL
    glClearColor(0.5f, 0.5f, 0.9f, 1);
    glClearDepthf(1);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    if (mb_cullface)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);        // good for debug
    glEnable(GL_TEXTURE_2D);

    //glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glAlphaFunc(GL_GREATER, 0.5);
    //glEnable(GL_ALPHA_TEST);

    m_anim.init(smart_path("data/animation/anim1.ani") );

    m_camera.lookat( Point(0,0,0), 15 );
    gl.light( Point(0, 10, 0), White() );

    init_axe();
    init_grid();
    init_cube(terrain->getnx(),50,terrain->getny());
    init_cube2(5,0.1,15);

    init_quad();
    init_cylindre(100,2.0,0.8);
    init_cone(100,3.0,1.5);
    init_sphere(50,2);
    init_bilboard();
    //init_pyramide();
    m_tex_mur = read_texture(0, smart_path("data/mur.png")) ;
    m_tex_pacman = read_texture(0, smart_path("data/pacman.png")) ;;
    m_tex_fantome = read_texture(0, smart_path("data/fantome.png")) ;;
    m_tex_pastille = read_texture(0, smart_path("data/pastille.png")) ;;
    Image img = read_image(smart_path("data/terrain/terrain_texture.png"));

    //texture= make_texture(0,img);
    texture = read_texture(0,smart_path("data/terrain/terrain_texture.png"));

    img = read_image(smart_path("data/cubemap/skybox.png"));
    texture_cube= make_texture(1,img);
    img = read_image(smart_path("src/l2_lifgfx/text.jpg"));
    texture_t= make_texture(1,img);
    img = read_image(smart_path("src/l2_lifgfx/index.jpeg"));
    texture_f= make_texture(1,img);
    img = read_image(smart_path("src/l2_lifgfx/eau.jpg"));
    texture_e= make_texture(1,img);
    img = read_image(smart_path("data/billboard/arbre.png"));
    texture_b= make_texture(1,img);
    Tplane=1;
    return 0;
}





void Viewer::init_axe()
{
    m_axe = Mesh(GL_LINES);
    m_axe.color( Color(1, 0, 0));
    m_axe.vertex( 0,  0, 0);
    m_axe.vertex( 1,  0, 0);

    m_axe.color( Color(0, 1, 0));
    m_axe.vertex( 0,  0, 0);
    m_axe.vertex( 0,  1, 0);

    m_axe.color( Color( 0, 0, 1));
    m_axe.vertex( 0,  0, 0);
    m_axe.vertex( 0,  0, 1);
}


void Viewer::init_grid()
{
    m_grid = Mesh(GL_LINES);

    m_grid.color( Color(1, 1, 1));
    int i,j;
    for(i=-5;i<=5;++i)
        for(j=-5;j<=5;++j)
        {
            m_grid.vertex( -5, 0, j);
            m_grid.vertex( 5, 0,  j);

            m_grid.vertex( i, 0, -5);
            m_grid.vertex( i, 0, 5);
        }
}

void Viewer::init_bilboard()
{
float points[4][3] = {{0,0,0},{1,0,0},{0,0,1},{1,0,1}};
  int faces[4] = {0,1,3,2};
  static float n[3] = {0,1,0};
  m_bilboard = Mesh(GL_TRIANGLE_STRIP);
    m_bilboard.normal(  n[0], n[1], n[2] );

    m_bilboard.texcoord( 0,0 );
    m_bilboard.vertex( points[faces[0] ][0], points[ faces[0] ][1], points[ faces[0] ][2] );

    m_bilboard.texcoord( 1,0);
    m_bilboard.vertex( points[ faces[1] ][0], points[ faces[1] ][1], points[ faces[1] ][2] );

    m_bilboard.texcoord(0,1);
    m_bilboard.vertex(points[ faces[3] ][0], points[ faces[3] ][1], points[ faces[3] ][2] );

    m_bilboard.texcoord(1,1);
    m_bilboard.vertex( points[ faces[2] ][0], points[ faces[2] ][1], points[ faces[2] ][2] );

    m_bilboard.restart_strip();

}

void Viewer::init_sphere(int n, float r)
{
  float alpha,alpha1,beta;
  m_sphere=Mesh(GL_TRIANGLE_STRIP);
  m_sphere.color(Color(1,1,1));
  for(int i = 0; i<= n;i++)
    {
      alpha=2*float(i)*M_PI/n;
      alpha1= 2*float(i+1)*M_PI/n;
      for(int j =0;j<=n;j++)
	{
	  beta=2*j*M_PI/n;
	  m_sphere.normal(Vector(cos(alpha1)*cos(beta),sin(alpha1),cos(alpha1)*sin(beta)));
	  m_sphere.texcoord(alpha,beta);
	  m_sphere.vertex(Point(r*cos(alpha1)*cos(beta),r*sin(alpha1),r*cos(alpha1)*sin(beta)));
	  m_sphere.normal(Vector(cos(alpha)*cos(beta),sin(alpha),cos(alpha)*sin(beta)));
	  m_sphere.texcoord(alpha1,beta);
	  m_sphere.vertex(Point(r*cos(alpha)*cos(beta),r*sin(alpha),r*cos(alpha)*sin(beta)));
	}
    }
}

void Viewer::init_forme(int n, float r)
{
  float alpha,alpha1,beta;
  m_sphere2=Mesh(GL_TRIANGLE_STRIP);
  m_sphere2.color(Color(1,1,1));
  for(int i = 0; i<= n;i++)
    {
      alpha=2*i*M_PI/n;
      alpha1= 2*(i+1)*M_PI/n;
      for(int j =0;j<=n;j++)
	{
	  beta=2*j*M_PI/n;
	  m_sphere2.normal(Vector(cos(alpha)*cos(beta),sin(alpha),sin(alpha)*sin(beta)));
	  m_sphere2.vertex(Point(r*cos(alpha)*cos(beta),r*sin(alpha),r*sin(alpha)*sin(beta)));
	  m_sphere2.normal(Vector(cos(alpha1)*cos(beta),sin(alpha1),sin(alpha1)*sin(beta)));
	  m_sphere2.vertex(Point(r*cos(alpha1)*cos(beta),r*sin(alpha1),r*sin(alpha1)*sin(beta)));
	}
    }
}

void Viewer::init_cylindre(int n,float h,float r)
{
  float pt[n+1][3];
  static float pn[2][3]={{0,0,0},{0,0,h}};
  static float nm[2][3]={{0,0,-1},{0,0,1}};
  float nk[n+1][3];
  int i,l;
  for(i=0;i<=n;i++)
    {
      nk[i][0]=cos(2*M_PI*i/n);
      nk[i][1]=sin(2*M_PI*i/n);
      nk[i][2]=0;
      pt[i][0]=r*cos(2*M_PI*i/n);
      pt[i][1]=r*sin(2*M_PI*i/n);
      pt[i][2]=0;
    }
    m_cylindre = Mesh(GL_TRIANGLE_STRIP);
    m_cylindre.color( Color(1,1,1));
    for (l=0;l<n;l++)
     {
        //face basse
        m_cylindre.normal(nm[0][0],nm[0][1],nm[0][2]);
        m_cylindre.normal(nk[l][0],nk[l][1],nk[l][2]);
        m_cylindre.normal(nk[l+1][0],nk[l+1][1],nk[l+1][2]);
        m_cylindre.texcoord(0,0);
        m_cylindre.vertex(pn[0][0],pn[0][1],pn[0][2]);
        m_cylindre.texcoord(1,0);
        m_cylindre.vertex(pt[l+1][0],pt[l+1][1],pt[l+1][2]);
        m_cylindre.texcoord(0,1);
        m_cylindre.vertex(pt[l][0],pt[l][1],pt[l][2]);
        m_cylindre.restart_strip();
        //triangle droit
        m_cylindre.normal(nk[l][0],nk[l][1],nk[l][2]);
        m_cylindre.normal(nk[l][0],nk[l][1],nk[l][2]+h);
        m_cylindre.normal(nk[l+1][0],nk[l+1][1],nk[l+1][2]+h);
        m_cylindre.texcoord(0,0);
        m_cylindre.vertex(pt[l][0],pt[l][1],pt[l][2]);
        m_cylindre.texcoord(1,0);
        m_cylindre.vertex(pt[l+1][0],pt[l+1][1],pt[l+1][2]+h);
        m_cylindre.texcoord(0,1);
        m_cylindre.vertex(pt[l][0],pt[l][1],pt[l][2]+h);
        m_cylindre.restart_strip();
        //triangle gauche
        m_cylindre.normal(nk[l][0],nk[l][1],nk[l][2]);
        m_cylindre.normal(nk[l][0],nk[l][1],nk[l][2]+h);
        m_cylindre.normal(nk[l+1][0],nk[l+1][1],nk[l+1][2]);
        m_cylindre.texcoord(0,0);
        m_cylindre.vertex(pt[l][0],pt[l][1],pt[l][2]);
        m_cylindre.texcoord(1,0);
        m_cylindre.vertex(pt[l+1][0],pt[l+1][1],pt[l+1][2]);
        m_cylindre.texcoord(0,1);
        m_cylindre.vertex(pt[l+1][0],pt[l+1][1],pt[l+1][2]+h);
        m_cylindre.restart_strip();
        //face haute
        m_cylindre.normal(nm[1][0],nm[1][1],nm[1][2]);
        m_cylindre.normal(nk[l][0],nk[l][1],nk[l][2]+h);
        m_cylindre.normal(nk[l+1][0],nk[l+1][1],nk[l+1][2]+h);
        m_cylindre.texcoord(0,0);
        m_cylindre.vertex(pn[1][0],pn[1][1],pn[1][2]);
        m_cylindre.texcoord(1,0);
        m_cylindre.vertex(pt[l][0],pt[l][1],pt[l][2]+h);
        m_cylindre.texcoord(0,1);
        m_cylindre.vertex(pt[l+1][0],pt[l+1][1],pt[l+1][2]+h);
        m_cylindre.restart_strip();
     }
}

void Viewer::init_cone(int n,float h,float r)
{
  float pt[n+1][3];
  static float pn[2][3]={{0,0,0},{0,0,h}};
  static float nm[2][3]={{0,0,-1},{0,0,1}};
  float nk[n+1][3];
  int i,l;
  for(i=0;i<=n;i++)
    {
      nk[i][0]=cos(2*M_PI*i/n);
      nk[i][1]=sin(2*M_PI*i/n);
      nk[i][2]=0;
      pt[i][0]=r*cos(2*M_PI*i/n);
      pt[i][1]=r*sin(2*M_PI*i/n);
      pt[i][2]=0;
    }
    m_cone = Mesh(GL_TRIANGLE_STRIP);
    m_cone.color( Color(1,1,1));
    for (l=0;l<n;l++)
     {
        //triangle face basse
        m_cone.normal(nm[0][0],nm[0][1],nm[0][2]);
        m_cone.normal(nk[l][0],nk[l][1],nk[l][2]);
        m_cone.normal(nk[l+1][0],nk[l+1][1],nk[l+1][2]);
        m_cone.texcoord(0,0);
        m_cone.vertex(pn[0][0],pn[0][1],pn[0][2]);
        m_cone.texcoord(1,0);
        m_cone.vertex(pt[l+1][0],pt[l+1][1],pt[l+1][2]);
        m_cone.texcoord(0,1);
        m_cone.vertex(pt[l][0],pt[l][1],pt[l][2]);
        m_cone.restart_strip();
        //triangle droit
        m_cone.normal(nm[1][0],nm[1][1],nm[1][2]);
        m_cone.normal(nk[l][0],nk[l][1],nk[l][2]);
        m_cone.normal(nk[l+1][0],nk[l+1][1],nk[l+1][2]);
        m_cone.texcoord(0,0);
        m_cone.vertex(pn[1][0],pn[1][1],pn[1][2]+h);
        m_cone.texcoord(1,0);
        m_cone.vertex(pt[l][0],pt[l][1],pt[l][2]);
        m_cone.texcoord(0,1);
        m_cone.vertex(pt[l+1][0],pt[l+1][1],pt[l+1][2]);
        m_cone.restart_strip();
     }
}

/*void Viewer::init_cone2(int n, float r, float h)
{
  float faces[n][]
}*/
/*void Viewer::init_boule(int n,float r)
{
    static float pt[6][n][3];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;i++)
        {

        }
    }
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    int i,j;
    m_cube = Mesh(GL_TRIANGLE_STRIP);
    m_cube.color( Color(1, 1, 1) );

    m_cube_texture = read_texture(0, smart_path("data/debug2x2red.png")) ;

    for (i=0;i<6;i++)
    {
        m_cube.normal(  n[i][0], n[i][1], n[i][2] );

        m_cube.texcoord( 0,0 );
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

        m_cube.texcoord( 1,0);
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

        m_cube.texcoord(0,1);
        m_cube.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

        m_cube.texcoord(1,1);
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

        m_cube.restart_strip();
    }
    m_boule = Mesh(GL_TRIANGLE_STRIP);
    m_boule.color( Color(1, 1, 1) );

    m_cube_texture = read_texture(0, smart_path("data/debug2x2red.png")) ;

    for (i=0;i<6;i++)
    {
        m_cube.normal(  n[i][0], n[i][1], n[i][2] );

        m_cube.texcoord( 0,0 );
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

        m_cube.texcoord( 1,0);
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

        m_cube.texcoord(0,1);
        m_cube.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

        m_cube.texcoord(1,1);
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

        m_cube.restart_strip();
    }
}*/

void Viewer::draw_avion(const Transform& T,unsigned int tex)
{
    draw_sphere(T*RotationX(-90)*Scale(7,1,1),tex);
    draw_cube2(T,tex);
    draw_cube2(T*RotationX(180)*Translation(0,-0.1,0),tex);
    draw_cube2(T*RotationX(-90)*Translation(-5.9,0,0)*Scale(0.3,0.4,0.2),tex);
    draw_cube2(T*Translation(-5.9,0,0)*Scale(0.3,0.4,0.2),tex);
    draw_cube2(T*RotationX(180)*Translation(-5.9,0,0)*Scale(0.3,0.4,0.2),tex);
    draw_sphere(T*RotationX(-90)*Scale(2,0.5,0.5)*Translation(0.5,8,-1),tex);
    draw_sphere(T*RotationX(-90)*Scale(2,0.5,0.5)*Translation(0.5,-8,-1),tex);
}

/*{
    //                          0           1           2       3           4           5       6           7
    static float pt[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,1,-1}, {1,1,-1}, {1,1,1}, {-1,1,1} };
    static int f[6][4] = {    {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    int i,j;

    m_cube = Mesh(GL_TRIANGLE_STRIP);
    m_cube.color( Color(1, 1, 1) );

    m_cube_texture = read_texture(0, smart_path("data/debug2x2red.png")) ;

    for (i=0;i<6;i++)
    {
        m_cube.normal(  n[i][0], n[i][1], n[i][2] );

        m_cube.texcoord( 0,0 );
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

        m_cube.texcoord( 1,0);
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );

        m_cube.texcoord(0,1);
        m_cube.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

        m_cube.texcoord(1,1);
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );

        m_cube.restart_strip();
    }
}*/

void Viewer::init_cube2(float L,float l,float h)
{
  float points[8][3] = {{0,0,0},{L,0,0},{0,0,h},{L,0,h},{L,l,0},{L,l,h},{0,l,h},{0,l,0}};
  int faces[6][4] = {{0,1,3,2},{5,4,7,6},{2,6,7,0},{1,4,5,3},{0,7,4,1},{2,3,5,6}};
  static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
  m_cube2 = Mesh(GL_TRIANGLE_STRIP);
  m_cube2.color( Color(1, 1, 1, 1) );
  for(int i=0;i<6;i++)
  {
    m_cube2.normal(  n[i][0], n[i][1], n[i][2] );

    m_cube2.texcoord( 0,0 );
    m_cube2.vertex( points[ faces[i][0] ][0], points[ faces[i][0] ][1], points[ faces[i][0] ][2] );

    m_cube2.texcoord( 1,0);
    m_cube2.vertex( points[ faces[i][1] ][0], points[ faces[i][1] ][1], points[ faces[i][1] ][2] );

    m_cube2.texcoord(0,1);
    m_cube2.vertex(points[ faces[i][3] ][0], points[ faces[i][3] ][1], points[ faces[i][3] ][2] );

    m_cube2.texcoord(1,1);
    m_cube2.vertex( points[ faces[i][2] ][0], points[ faces[i][2] ][1], points[ faces[i][2] ][2] );

    m_cube2.restart_strip();
  }
}

void Viewer::init_cube(float L,float l,float h)
{
  float pt[8][3] = {{0,0,0},{L,0,0},{L,0,h},{0,0,h},{0,l,0},{L,l,0},{L,l,h},{0,l,h}};
  static int f[6][4] = {    {0,1,2,3}, {5,4,7,6}, {2,1,5,6}, {0,3,7,4}, {3,2,6,7}, {1,0,4,5} };
  static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
  float tex[6][8]={   {0.25,  0.3, 0.5, 0.33,0.25, 0 , 0.5, 0},{0.25, 1, 0.25, 0.66, 0.5, 1, 0.5, 0.66},{ 0.5, 0.66, 0.75, 0.66, 0.5, 0.33, 0.75, 0.33},{0, 0.66, 0.25, 0.66, 0, 0.33, 0.25, 0.33},{0.25,0.66,0.5,0.66,0.25,0.33,0.5,0.33},{0.75,0.66,1,0.66,0.75,0.33,1,0.33}};
  m_cube = Mesh(GL_TRIANGLE_STRIP);
  m_cube.color( Color(1, 1, 1) );
  for(int i=0;i<6;i++)
  {
    m_cube.normal( 1,1,1 );


        m_cube.texcoord(tex[i][0],tex[i][1]);
        m_cube.vertex(pt[ f[i][3] ][0], pt[ f[i][3] ][1], pt[ f[i][3] ][2] );

        m_cube.texcoord(tex[i][2],tex[i][3]);
        m_cube.vertex( pt[ f[i][2] ][0], pt[ f[i][2] ][1], pt[ f[i][2] ][2] );


        m_cube.texcoord( tex[i][4],tex[i][5] );
        m_cube.vertex( pt[ f[i][0] ][0], pt[ f[i][0] ][1], pt[ f[i][0] ][2] );

        m_cube.texcoord( tex[i][6],tex[i][7]);
        m_cube.vertex( pt[ f[i][1] ][0], pt[ f[i][1] ][1], pt[ f[i][1] ][2] );
        m_cube.restart_strip();
  }
}

/*void Viewer::init_pyramide()
{
  float points[4][3] = {{-1,1,0},{-1,-1,0},{1,0,0},{0,0,5}};
  float normal[4][3] = {{0,0,-1},{-1,1,1},{1,0,1},{1,-1,1}};
  int faces[4][3] = {{1,2,3},{1,4,2},{1,3,4},{2,4,3}};
  m_pyramide = Mesh(GL_TRIANGLE_STRIP);
  m_pyramide.color(Color(1,1,1));
  for (int i = 0; i < 4; i++)
  {
    m_pyramide.normal(normal[i][0],normal[i][1],normal[i][2]);
    m_pyramide.texcoord(0,0);
    m_pyramide.vertex(points[faces[i][0]][0], points[faces[i][0]][1],points[faces[i][0]][2]);
    m_pyramide.texcoord(1,0);
    m_pyramide.vertex(points[faces[i][1]][0], points[faces[i][1]][1],points[faces[i][1]][2]);
    m_pyramide.texcoord(0,1);
    m_pyramide.vertex(points[faces[i][2]][0], points[faces[i][2]][1],points[faces[i][2]][2]);
    m_pyramide.restart_strip();

  }
}*/

void Viewer::init_quad()
{
    m_quad = Mesh(GL_TRIANGLE_STRIP);
    m_quad.color( Color(1, 1, 1));
    m_quad_texture = read_texture(0, smart_path("data/papillon.png") );

    m_quad.normal(  0, 0, 1 );

    m_quad.texcoord(0,0 );
    m_quad.vertex(-1, -1, 0 );

    m_quad.texcoord(1,0);
    m_quad.vertex(  1, -1, 0 );

    m_quad.texcoord(0,1);
    m_quad.vertex( -1, 1, 0 );

    m_quad.texcoord( 1,1);
    m_quad.vertex(  1,  1, 0 );
}



void Viewer::draw_pacman(const Transform& T)
{
    int i,j;
    draw_cube( T*Translation( m_pacman.getConstPacman().getX(),m_pacman.getConstPacman().getY(),0), m_tex_pacman);
    draw_cube( T*Translation( m_pacman.getConstFantome().getX(),m_pacman.getConstFantome().getY(),0), m_tex_fantome);

    for(i=0;i<m_pacman.getTerrain().getDimX();++i)
        for(j=0;j<m_pacman.getTerrain().getDimY();++j)
        {
            if (m_pacman.getTerrain().getXY(i,j)=='#')
                draw_cube( T*Translation(i,j,0), m_tex_mur);
            else
            if (m_pacman.getTerrain().getXY(i,j)=='.')
                draw_cube( T*Translation(i,j,0), m_tex_pastille);
            //else
//                draw_cube( T*Translation(i,j,0), 0);
        }
}




int Viewer::render( )
{
    // Efface l'ecran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Deplace la camera, lumiere, etc.
    manageCameraLight();

    // donne notre camera au shader
    gl.camera(m_camera);


    gl.model(Tquad);
    //draw_cube(1,texture);
    draw_terrain(Translation(-5,0,-5)*Scale(0.1,0.1,0.1),texture);
    draw_terrain2(Translation(0,0.2,0),texture_e);
    draw_avion(Tplane*RotationY(-90)*Scale(0.1,0.1,0.1)*Translation(0,20,0),0);
    /*for(int i=0;i<image.width()-1;i+=30)
    {
      for(int j=0;j<image.height();j+=30)
      {
          if(terrain->Elevation(i+1,j,image)*0.12>0.2)
          {
            draw_arbre(Translation(-5,0,-5)*Scale(0.05,0.135,0.05)*Translation(i+1,terrain->Elevation(i+1,j,image),j),0);
          }
      }
    }*/
    for(int j=0;j<20;j++)
    {
      draw_arbre2(Translation(-5,0,-5)*Translation(T[j].x*0.05,T[j].y*0.05,T[j].z*0.05)*RotationX(-90),0);
      }
    draw_cube(Scale(0.1,0.1,0.1)*Translation(-50,0,-50),texture_cube);

    return 1;
}





int Viewer::update( const float time, const float delta )
{
    Tquad = Translation( 3, 5, 0 ) * Rotation( Vector(0,0,1), 0.1f*time);

    m_pacman.actionsAutomatiques();
    if (key_state(SDLK_RIGHT) && key_state(SDLK_LALT)) m_pacman.actionClavier('d');
    if (key_state(SDLK_LEFT) && key_state(SDLK_LALT)) m_pacman.actionClavier('g');
    if (key_state(SDLK_UP) && key_state(SDLK_LALT)) m_pacman.actionClavier('h');
    if (key_state(SDLK_DOWN) && key_state(SDLK_LALT)) m_pacman.actionClavier('b');


    float ts = 10*time/1000;
    int temps_entier = int (ts);

    int temps_entier_ok = temps_entier % m_anim.nb_points();
    float poids = ts - temps_entier;
    int cible = (temps_entier + 1) % m_anim.nb_points();

    Point pos = m_anim[temps_entier_ok] + (m_anim[cible]-m_anim[temps_entier_ok])*poids;


    int prec1 = (temps_entier +1) % m_anim.nb_points();
    int suiv1 = (cible +1) % m_anim.nb_points();

    Point pos_suiv = m_anim[prec1] + poids * (m_anim[suiv1]-m_anim[prec1]);

    Vector direction = normalize(pos_suiv - pos);
    float ps = dot(direction,Vector(1,0,0));
    float angle;
    if (direction.z>0) angle = -acos(ps);
    else angle = acos(ps);



    Tplane = Translation((pos_suiv.x+(pos.x-pos_suiv.x)*poids*0.05)/5, 0,  (pos_suiv.z+(pos.z-pos_suiv.z)*poids*0.05)/5)*RotationY((angle/M_PI)*180 +90.0);

    return 1;
}

void Viewer::draw_terrain(const Transform& T, unsigned int tex)
{
  gl.model(T*Scale(0.5,0.5,0.5));
    gl.texture(tex);

    Mesh test=terrain->creationM();
    gl.draw(test);
    //gl.lighting(true);
}

void Viewer::draw_terrain2(const Transform& T, unsigned int tex)
{
  gl.model(T*Scale(0.5,0.5,0.5));
    gl.texture(tex);

    Mesh test=terrain2->creationM();
    gl.draw(test);
    //gl.lighting(true);
}




void Viewer::draw_cylindre(const Transform& T, unsigned int tex)
{
  gl.model(T*Scale(0.5,0.5,0.5));
    gl.texture(tex);
    //gl.lighting(false);
    gl.draw(m_cylindre);
    //gl.lighting(true);
}

void Viewer::draw_cone(const Transform& T, unsigned int tex)
{
   gl.model(T*Scale(0.5,0.5,0.5));
    gl.texture(tex);
    //gl.lighting(false);
    gl.draw(m_cone);
    //gl.lighting(true);
}
void Viewer::draw_arbre(const Transform& T, unsigned int tex)
{
  //gl.model(T*Scale(0.5,0.5,0.5));
  draw_cylindre(T*RotationX(-90),texture_t);
  draw_cone(T*Translation(0,1,0)*RotationX(-90),texture_f);
}

void Viewer::draw_arbre2(const Transform& T, unsigned int tex)
{
    gl.model(T*Translation(-0.25,0,0)*Scale(0.5,0.5,0.5));
    gl.alpha(1.0);
    gl.texture(texture_b);
    gl.draw(m_bilboard);
    gl.model(T*Translation(0,0.25,0)*RotationZ(-90)*Scale(0.5,0.5,0.5));
    gl.draw(m_bilboard);
    gl.model(T*Translation(0,-0.25,0)*RotationZ(-270)*Scale(0.5,0.5,0.5));

    gl.draw(m_bilboard);
    gl.model(T*Translation(0.25,0,0)*RotationZ(-180)*Scale(0.5,0.5,0.5));

    gl.draw(m_bilboard);
    gl.alpha(0.0);

}


void Viewer::draw_axe(const Transform& T)
{
    gl.model(T);
    gl.texture(0);
    gl.lighting(false);
    gl.draw(m_axe);
    gl.lighting(true);
}

void Viewer::draw_sphere(const Transform& T, unsigned int tex)
{
    gl.model(T*Scale(0.5,0.5,0.5));
    gl.texture(tex);
    //gl.lighting(false);
    gl.draw(m_sphere);
    //gl.lighting(true);
}

void Viewer::draw_cube2(const Transform& T, unsigned int tex)
{
    gl.model(T*Scale(0.5,0.5,0.5));
    gl.texture(tex);
    //gl.lighting(false);
    gl.draw(m_cube2);
    //gl.lighting(true);
}

void Viewer::draw_cube(const Transform& T, unsigned int tex)
{
    gl.model(T*Scale(0.5,0.5,0.5));
    gl.texture(tex);
    //gl.lighting(false);
    gl.draw(m_cube);
    //gl.lighting(true);
}


void Viewer::manageCameraLight()
{
    // recupere les mouvements de la souris pour deplacer la camera, cf tutos/tuto6.cpp
    int mx, my;
    unsigned int mb= SDL_GetRelativeMouseState(&mx, &my);
    // deplace la camera
    if((mb & SDL_BUTTON(1)) &&  (mb& SDL_BUTTON(3)))                 // le bouton du milieu est enfonce
        m_camera.translation( (float) mx / (float) window_width(), (float) my / (float) window_height());         // deplace le point de rotation
    else if(mb & SDL_BUTTON(1))                      // le bouton gauche est enfonce
        m_camera.rotation( mx, my);       // tourne autour de l'objet
    else if(mb & SDL_BUTTON(3))                 // le bouton droit est enfonce
        m_camera.move( my);               // approche / eloigne l'objet
    if (key_state(SDLK_PAGEUP) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT)) ) { m_camera.translation( 0,0.01); }
    if (key_state(SDLK_PAGEDOWN) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT)) ) { m_camera.translation( 0,-0.01); }
    if (key_state(SDLK_LEFT) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT)) ) { m_camera.translation(  0.01,0); }
    if (key_state(SDLK_RIGHT) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT)) ) { m_camera.translation( -0.01,0); }
    if (key_state(SDLK_UP) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT))) { m_camera.move( 1); }
    if (key_state(SDLK_DOWN) && (!key_state(SDLK_LCTRL)) && (!key_state(SDLK_LALT))) { m_camera.move( -1); }


    // Deplace la lumiere
    const float step = 0.1f;
    if (key_state(SDLK_RIGHT) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(step,0,0)); }
    if (key_state(SDLK_LEFT) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(-step,0,0)); }
    if (key_state(SDLK_UP) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(0,0,-step)); }
    if (key_state(SDLK_DOWN) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(0,0,step)); }
    if (key_state(SDLK_PAGEUP) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(0,step,0)); }
    if (key_state(SDLK_PAGEDOWN) && key_state(SDLK_LCTRL)) { gl.light( gl.light()+Vector(0,-step,0)); }



    // (De)Active la grille / les axes
    if (key_state('h')) help();
    if (key_state('c')) { clear_key_state('c'); mb_cullface=!mb_cullface; if (mb_cullface) glEnable(GL_CULL_FACE);else glDisable(GL_CULL_FACE); }
    if (key_state('w')) { clear_key_state('w'); mb_wireframe=!mb_wireframe; if (mb_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    if (key_state('g')) { b_draw_grid = !b_draw_grid; clear_key_state('g'); }
    if (key_state('a')) { b_draw_axe = !b_draw_axe; clear_key_state('a'); }
    if (key_state('z')) { b_draw_animation=!b_draw_animation; clear_key_state('z');}

    gl.camera(m_camera);
    //draw(cube, Translation( Vector( gl.light()))*Scale(0.3, 0.3, 0.3), camera);
    //draw_param.texture(quad_texture).camera(camera).model(Translation( 3, 5, 0 )).draw(quad);

    // AXE et GRILLE
    gl.model( Identity() );
    if (b_draw_grid) gl.draw(m_grid);
    if (b_draw_axe) gl.draw(m_axe);
    if (b_draw_animation) m_anim.draw(m_camera);

     // LIGHT
    gl.texture( 0 );
    gl.lighting(false);
    gl.model( Translation( Vector( gl.light()))*Scale(0.3, 0.3, 0.3) );
    gl.draw(m_cube);
    gl.lighting(true);
}

int Viewer::quit( )
{
    return 0;
}
