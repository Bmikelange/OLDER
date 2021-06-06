#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "../main/jeu.h"
using namespace std;

int main()
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    int terminer = 0;
    int nivsuiv = 0;
    int reussi = 2;
    int nbCoup = 0;
    TableauDynamique * tabA;
    TableauDynamique * tabB;
    char test;
    string test1;
	jeu jeu1;
	jeu1.InitJeu();
  niveau niveau2;
  jeu1.aleatoireGen(niveau2,4);
  tabA=niveau2.getListe();
  tabB=niveau2.getListeTransfert();
  tabB->ajouterElement(1);
  tabB->taille_utilisee=0;
  reussi=jeu1.jeuAction(*tabA,*tabB,niveau2,1,nbCoup);
while (terminer == 0)
    {
        if(reussi==2)
        {
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif
            cout<<"que voulez vous faire?"<<endl;
            cout<<" q = quitter et sauvegarder \n choix du niveau \n\n";
            for(int j=1;j<=4;j++)
            {
                if(jeu1.Getniveau(j-1).getNbEtoilePourDebloquer()<=jeu1.GettotalEtoile())
                {
                    cout<<j<<" : niveau "<< j;
                    if(jeu1.Getniveau(j-1).getReussi()==1)
                    {
                        cout<<"     reussi avec "<< jeu1.Getniveau(j-1).getEtoile() <<" etoiles";
                    }
                    cout<<endl;
                }
            }
            string testCmp="q";
            cin >> test1;
            if (!(strcmp(test1.c_str(),testCmp.c_str())))
            {
                jeu1.SaveJeu();
                terminer =1;
            }
            else if(atoi(test1.c_str())<10 && atoi(test1.c_str()))
            {
                if(jeu1.Getniveau(atoi(test1.c_str())-1).getNbEtoilePourDebloquer()<=jeu1.GettotalEtoile())
                {
                    jeu1.afficheHistoire(atoi(test1.c_str())-1);
                    tabA=jeu1.Getniveau(atoi(test1.c_str())-1).getListe();
                    tabB=jeu1.Getniveau(atoi(test1.c_str())-1).getListeTransfert();
                    tabB->ajouterElement(1);
                    tabB->taille_utilisee=0;
                    reussi=jeu1.jeuAction(*tabA,*tabB,jeu1.Getniveau(atoi(test1.c_str())-1),atoi(test1.c_str()),nbCoup);
                }
            }
        }
        if(reussi==0)
        {
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif
            cout<<"PERDU"<<endl;
            cout<<"que voulez vous faire"<<endl;
            cout<<"a = rejouer \n q = retourner a la liste de choix des niveaux \n";
            cin >> test;
            nbCoup=0;
            switch(test)
            {
            case 'a' :
                jeu1.afficheHistoire(atoi(test1.c_str())-1+nivsuiv);
                reussi=jeu1.jeuAction(*tabA,*tabB,jeu1.Getniveau((atoi(test1.c_str())-1+nivsuiv)),atoi(test1.c_str())+nivsuiv,nbCoup);
                break;
            case 'q' :
                reussi =2;
                nivsuiv=0;
                break;
            }
        }
        if(reussi==1)
        {
            jeu1.setVp(atoi(test1.c_str())-1 + nivsuiv,nbCoup);
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif
            cout<<"REUSSI"<<endl;
            cout<<"que voulez vous faire"<<endl;
            cout<<"a = rejouer \n z= aller au niveau suivant \n q = retourner a la liste de choix des niveaux \n";
            nbCoup=0;
            cin >> test;
            switch(test)
            {
            case 'a' :
                reussi=jeu1.jeuAction(*tabA,*tabB,jeu1.Getniveau(atoi(test1.c_str())-1+nivsuiv),atoi(test1.c_str())+nivsuiv,nbCoup);
                break;
            case 'z' :
                if(jeu1.Getniveau(atoi(test1.c_str())-1 + nivsuiv).getNbEtoilePourDebloquer()<=jeu1.GettotalEtoile())
                {
                    nivsuiv++;
                    jeu1.afficheHistoire(atoi(test1.c_str())-1+nivsuiv);
                    tabA=jeu1.Getniveau(atoi(test1.c_str())-1 + nivsuiv).getListe();
                    tabA->capacite=jeu1.Getniveau(atoi(test1.c_str())-1 + nivsuiv).getListe()->capacite;
                    tabA->taille_utilisee=jeu1.Getniveau(atoi(test1.c_str())-1 + nivsuiv).getListe()->taille_utilisee;
                    tabB=jeu1.Getniveau(atoi(test1.c_str())-1 + nivsuiv).getListeTransfert();
                    tabB->ad[0]=1;
                    reussi=jeu1.jeuAction(*tabA,*tabB,jeu1.Getniveau(atoi(test1.c_str())-1 + nivsuiv),atoi(test1.c_str())+nivsuiv,nbCoup);
                }
                break;
            case 'q' :
                reussi = 2;
                nivsuiv=0;
                break;
            }
        }
    }
  return (0);
} /*main*/
