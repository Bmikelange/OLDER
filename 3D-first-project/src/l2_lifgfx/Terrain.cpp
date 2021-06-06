#include "Ter.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>

#include <time.h>

#include "draw.h"        // pour dessiner du point de vue d'une camera


using namespace std;

int Ter::trouverPosition(int i,int j)
{
    return i+j*nx;
}

Ter::Ter(int va[2],int vb[2],int i, int j)
{
    a[0]=va[0];
    a[1]=va[1];
    b[0]=vb[0];
    b[1]=vb[1];
    nx = i;
    ny = j;
    z.resize(nx*ny,1);
    srand((unsigned int)time(NULL));
    for(int i=0;i<ny;i++)
    {
        for(int j=0;j<nx;j++)
        {
                z[trouverPosition(j,i)]=0.0;
        }
    }
}

Ter::Ter(Image image,float z1, float z2)
{
    a[0]=0;
    a[1]=0;
    b[1]=image.height();
    b[0]=image.width();
    nx=image.width();
    ny=image.height();
    z.resize(nx*ny,1);
    for(int i=0;i<ny;i++)
    {
        for(int j=0;j<nx;j++)
        {
                z[trouverPosition(j,i)]=((image(j,i).r+image(j,i).g+image(j,i).b)/3)*30;
        }
    }


}


Point Ter::recupPoint(int i,int j)
{
    float x= a[0]+((b[0]-a[0])/(nx-1))*i;
    float y= a[1]+((b[1]-a[1])/(ny-1))*j;
    float z2=z[trouverPosition(i,j)];
    Point P={x,z2,y};
    return P;
}

Mesh Ter::creationM()
{
    Mesh terrain;
    terrain=Mesh(GL_TRIANGLE_STRIP);
    terrain.color(Color(1,1,1));
    for(int j=0;j<ny-1;j++)
    {
        for(int i=0;i<nx-1;i++)
        {
            Point p=recupPoint(i,j);
            Point p2=recupPoint(i,j+1);
            terrain.texcoord(float(i)/(nx-1),float(j)/(ny-1));
            terrain.vertex(p.x,p.y,p.z);
            terrain.texcoord(float(i)/(nx-1),float(j+1)/(ny-1));
            terrain.vertex(p2.x,p2.y,p2.z);
        }
        terrain.restart_strip();
    }
    return terrain;
}

float Ter::getd2(int i)
{
  return d[i];
}

int Ter::getnx()
{
  return nx;
}

int Ter::getny()
{
  return ny;
}

void Ter::aleaSurD(Image img)
{
  float u= (rand()%1001)/1000.0;
  float v= (rand()%1001)/1000.0;
  d[0]= rand()%img.height();
  d[1]= rand()%img.width();
}

void Ter::aleaSurD()
{
  float u= (rand()%1001)/1000.0;
  float v= (rand()%1001)/1000.0;
  d[0]= u*a[0]+(1-u)*b[0];
  d[1]= v*a[1]+(1-v)*b[1];
}

float Ter::Elevation(float V1,float V2,Image img)
{
  float z1=10*img(V1,V2).r+0.5;
  return z1;
}

float Ter::Elevation(float V1,float V2)
{
  float u= (V1-a[0])/(b[0]-a[0]);
  u *= nx-1;
  int ip=(int)u;
  float ul=u-ip;
  float v= (V2-a[1])/(b[1]-a[1]);
  v *= nx-1;
  int iq=(int)v;
  float vl=v-iq;
  float z1=(1-ul)*(1-vl)*z[trouverPosition(ip,iq)]+(ul)*(1-vl)*z[trouverPosition(ip+1,iq)]+(ul)*(vl)*z[trouverPosition(ip+1,iq+1)]+(1-ul)*(vl)*z[trouverPosition(ip,iq+1)];
  return z1;
}
