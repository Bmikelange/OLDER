#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <assert.h>
#include "./jeu.h"
#include "./client.h"
using namespace std;

jeu::jeu()
{
    chronometre=0;
    totalEtoile=0;
}

jeu::~jeu()
{
    //dtor
}

void jeu::InitJeu()
{
    for(int i=1;i<=4;i++)
    {
        niveaux[i-1].chargerNiveau(i);
    }
    ifstream work ("./data/jeu/jeu");
    if(work.is_open())
    {
        work >> totalEtoile;
    }
    work.close();
}

void jeu::SaveJeu()
{
    ofstream work ("./data/jeu/jeu");
    if(work.is_open())
    {
        work << totalEtoile;
    }
    work.close();
    for(int i=1;i<=4;i++)
    {
        niveaux[i-1].sauveNiveau(i);
    }

}

int jeu::modifChrono(struct tm timer)
{
    time_t timed;
    time(&timed);
    chronometre=(int)difftime(mktime(&timer),timed);
    cout<<chronometre<<endl;
    return chronometre;
}
int jeu::modifChronograph(struct tm timer)
{
    time_t timed;
    time(&timed);
    chronometre=(int)difftime(mktime(&timer),timed);
    return chronometre;
}

int jeu::verifOrdre(TableauDynamique tab)
{
    for(unsigned int i=0;i<tab.taille_utilisee-1;i++)
    {
        if(tab.ad[i]>tab.ad[i+1])
        {
            return 0;
        }
    }
    return 1;
}

void jeu::afficheErreur()
{
    #ifdef _WIN32
        system("cls");
        system("Color FC");
        #else
        system("clear");
        #endif
        cout<< "utiliser une commande valide";
        #ifdef _WIN32
        Sleep(2500);
        system("Color 0F");
        #else
        sleep(2.5);
        #endif
}


int jeu::test(TableauDynamique tabA,TableauDynamique tabB,int i,struct tm * ttime)
{
    if(verifOrdre(tabA) && tabB.taille_utilisee==0)
    {
        #ifdef _WIN32
        Sleep(1000);
        #else
        sleep(1);
        #endif
        return 1;
    }
    cout<<"                   timer : ";
    if(i!=4)
    {
        if(modifChrono(*ttime)<=0)
        {
            #ifdef _WIN32
            Sleep(1000);
            #else
            sleep(1);
            #endif
            return 0;
        }
    }
    else
    {
        cout<< "bloque"<<endl;
    }
    return 2;
}

void jeu::afficherAction(TableauDynamique tabA,TableauDynamique tabB,niveau niveau1)
{
    cout<<" que voulez vous faire?"<<endl;
    cout<<" q = quitter \n";
    if(niveau1.getFonctionActivee(0)==1)
        cout<<" a = switch deux premier elements de A \n";
    if(niveau1.getFonctionActivee(1)==1)
        cout<<" s = switch deux premier elements de B \n";
    if(niveau1.getFonctionActivee(2)==1)
        cout<<" d = a et s en meme temps \n";
    if(niveau1.getFonctionActivee(3)==1)
        cout<<" f = push le premier element de A dans B \n";
    if(niveau1.getFonctionActivee(4)==1)
        cout<<" g = push le premier element de B dans A \n";
    if(niveau1.getFonctionActivee(5)==1)
        cout<<" h = met le premier element de A a la fin \n";
    if(niveau1.getFonctionActivee(6)==1)
        cout<<" j = met le premier element de B a la fin \n";
    if(niveau1.getFonctionActivee(7)==1)
        cout<<" k = h et j en meme temps \n";
    if(niveau1.getFonctionActivee(8)==1)
        cout<<" l = met le dernier element de A au debut \n";
    if(niveau1.getFonctionActivee(9)==1)
        cout<<" e = met le dernier element de B au debut \n";
    if(niveau1.getFonctionActivee(10)==1)
        cout<<" m = l et e en meme temps \n";
    cout<< "\n\n\n A | ";
    tabA.afficher();
    cout << " B | ";
    tabB.afficher();
    cout<<"\n action :"<<endl;
}

void jeu::afficheHistoire(int i)
{
    char t;
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    switch(i)
    {
    case 0:
        cout << "Bonjour,\n Bienvenue sur notre jeu de reflexion \n";
        cout << "Dans notre jeu, vous devrez trier les listes afficher a l'ecran en un minimum d'instruction.\n";
        cout << "attention au timer\n\n\n";
        cout << "nous allons vous expliquer les instructions de bases avec lesquelles vous commencerez.\n";
        cout << "d'autres instructions seront rajoutee au fur et a mesure du jeu.\n\n";
        cout << "a = inverse les deux premiers elements de la liste A\n";
        cout << "S = inverse les deux premiers elements de la liste B\n\n";
        break;
    case 1:
        cout << "Et oui nous revoila deja !!\n";
        cout << "nous allons vous debloquer deux nouvelles instruction\n\n\n";
        cout << "f = mets le premier element de A au debut de B\n";
        cout << "g = mets le premier element de B au debut de A\n\n";
        break;
    case 2:
        cout << "Rebonjour,\n";
        cout << "cette fois si il y a une seule nouvelle instruction.\n\n heureux?\n\n\n";
        cout << "d = effectue a et s en meme temps\n\n";
        break;
    case 3:
        cout << "bienvenu sur ce niveau de test,\n";
        cout << "ici vous pourrez tester toute les fonctionnalitées du jeu sans limite de temps.\n\n on espère que vous etes bien préparé\n\n\n";
        cout << "un recapitulatif des fonctionnalites sera donnes lors de la partie\n\n";
        break;
    }
     cout<< "appuyer sur une lettre pour quitter";
     cin >> t;
}

bool jeu::jeuAction(TableauDynamique tabA, TableauDynamique tabB,niveau niveau1,int i,int & m)
{
    int j;
    time_t timed;
    struct tm * tmtime;
    time(&timed);
    tmtime=localtime(&timed);
    tmtime->tm_min=tmtime->tm_min+1;
    while(1)
  {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    if((j=test(tabA,tabB,i,tmtime))==1)
    {
        return 1;
    }
    else if(j==0)
    {
        return 0;
    }
    afficherAction(tabA,tabB,niveau1);
    char test;
    cin>>test;
    switch(test)
      {
      case 'q' :
        return 0;
        break;
      case 'a' :
        if(niveau1.getFonctionActivee(0))
        {
            niveau1.sa(tabA);
            m++;
        }
        break;
      case 's' :
        if(niveau1.getFonctionActivee(1))
        {
            niveau1.sa(tabB);
            m++;
        }
        break;
      case 'd' :
        if(niveau1.getFonctionActivee(2))
        {
            niveau1.ss(tabA,tabB);
            m++;
        }
        break;
      case 'f' :
        if(niveau1.getFonctionActivee(3))
        {
            niveau1.pa(tabA,tabB);
            m++;
        }
        break;
      case 'g' :
        if(niveau1.getFonctionActivee(4))
        {
            niveau1.pa(tabB,tabA);
            m++;
        }
        break;
      case 'h' :
        if(niveau1.getFonctionActivee(5))
        {
            niveau1.ra(tabA);
            m++;
        }
        break;
      case 'j' :
        if(niveau1.getFonctionActivee(6))
        {
            niveau1.ra(tabB);
            m++;
        }
        break;
      case 'k' :
        if(niveau1.getFonctionActivee(7))
        {
            niveau1.rr(tabA,tabB);
            m++;
        }
        break;
      case 'l' :
        if(niveau1.getFonctionActivee(8))
        {
            niveau1.rra(tabA);
            m++;
        }
        break;
      case 'e' :
        if(niveau1.getFonctionActivee(9))
        {
            niveau1.rra(tabB);
            m++;
        }
        break;
      case 'm' :
        if(niveau1.getFonctionActivee(10))
        {
            niveau1.rrr(tabA,tabB);
            m++;
        }
        break;
      default :
        afficheErreur();
        break;
      }
  }
}

int jeu::verifnbCoup(niveau niveau,int nbCoup)
{
    if(nbCoup<=niveau.getNbCoupMax())
    {
        return(3);
    }
    if(nbCoup<=niveau.getNbCoupMax()*2)
    {
        return(2);
    }
    if(nbCoup<=niveau.getNbCoupMax()*3)
    {
        return(1);
    }
    return(0);
}

void jeu::setVp(int niveau,int nbCoup)
{
    Getniveau(niveau).setReussi(1);
    if(Getniveau(niveau).getEtoile()<3)
    {
        SetTotalEtoile(GettotalEtoile()+verifnbCoup(Getniveau(niveau),nbCoup)-Getniveau(niveau).getEtoile());
    }
    if(Getniveau(niveau).getEtoile()<verifnbCoup(Getniveau(niveau),nbCoup))
        {
            Getniveau(niveau).setEtoile(verifnbCoup(Getniveau(niveau),nbCoup));
        }
}

void jeu::aleatoireGen(niveau & niveau1,int n)
{
  niveau1.getListe()->vider();
  Sort sort1;
  srand(time(NULL));
  for(int j=0;j<n;j++)
  {
    int random=rand()%(99+1);
    if(niveau1.getListe()->rechercherElement(random)!=-1)
    {
      j--;
    }
    else{
      niveau1.setListe(j,random);
    }
  }
  TableauDynamique B;
  for(int m=0;m<n;m++)
  {
    B.ajouterElement(niveau1.getListe()->valeurIemeElement(m));
  }
  B.afficher();
  sort1.set_tabA(B);
  B.afficher();
  sort1.sort_array(B,0);
  cout<<"je suis la 2"<<endl;
  niveau1.setNbCoupMax(sort1.recupCount());
  niveau1.setEtoile(0);
  niveau1.setReussi(0);
  niveau1.setNbEtoilePourDebloquer(0);
  for(int i=0;i<11;i++)
  {
      niveau1.setFonctionActivee(i,1);
  }
}



void jeu::testRegression()
{
    for(int i=0;i<6;i++)
    {
        niveau1.getListe()->ajouterElement(i);
        assert(niveau1.getListe()->ad[i]==i);
    }
    assert(niveau1.getListe()->taille_utilisee==6);
    cout <<"test ajout d'elements passe"<<endl;
    niveau1.setReussi(0);
    niveau1.setEtoile(0);
	niveau1.setNbCoupMax(5);
	niveau1.setFonctionActivee(0,0);
	niveau1.setFonctionActivee(1,5);
	niveau1.setNbEtoilePourDebloquer(0);
	assert(niveau1.getReussi()==0);
	assert(niveau1.getEtoile()==0);
	assert(niveau1.getNbCoupMax()==5);
	assert(niveau1.getFonctionActivee(0)==0);
	assert(niveau1.getFonctionActivee(1)==5);
	assert(niveau1.getNbEtoilePourDebloquer()==0);
	cout <<"test de gestion des elements passe"<<endl;
	niveau1.sauveNiveau(0);
    niveau2.chargerNiveau(0);
    for(int i=0;i<6;i++)
    {
        assert(niveau2.getListe()->ad[i]==i);
    }
    assert(niveau2.getListe()->taille_utilisee==6);
	assert(niveau2.getReussi()==0);
	assert(niveau2.getEtoile()==0);
	assert(niveau2.getNbCoupMax()==5);
	assert(niveau2.getFonctionActivee(0)==0);
	assert(niveau2.getFonctionActivee(1)==5);
	assert(niveau2.getNbEtoilePourDebloquer()==0);
	cout <<"test de sauvegarde et lecture depuis un fichier passe"<<endl;
	niveau2.sa(*(niveau2.getListe()));
	assert(niveau2.getListe()->valeurIemeElement(0)==1 && niveau2.getListe()->valeurIemeElement(1)==0 );
	cout << "test de sa , sb et ss passe"<<endl;
	niveau2.pa(*(niveau2.getListe()),*(niveau2.getListeTransfert()));
	assert(niveau2.getListeTransfert()->valeurIemeElement(0)==1 && niveau2.getListe()->valeurIemeElement(0)==0 );
	cout << "test de pa et pb passe"<<endl;
	niveau2.rra(*(niveau2.getListe()));
	assert(niveau2.getListe()->valeurIemeElement(0)==5);
	assert(niveau2.getListe()->valeurIemeElement(1)==0);
	cout << "test de rra , rrb et rrr passe"<<endl;
	niveau2.ra(*(niveau2.getListe()));
	assert(niveau2.getListe()->valeurIemeElement(4)==5);
	assert(niveau2.getListe()->valeurIemeElement(0)==0);
	cout << "test de ra, rb et rr passe"<<endl;
}
