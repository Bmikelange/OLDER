#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <fstream>
#include <assert.h>
#include "push_swap.h"
using namespace std;

    niveau::niveau()
    {
        reussi=0;
        etoile = 0;
        for (int i=0;i<14;i++)
        {
            fonctionActivee[i]=1;
        }
        nbCoupMax=1;
        nbEtoilePourDebloquer=0;
    }

    void niveau::chargerNiveau(int i)
    {
    string niveau="./data/niveau/niveau";
    i += 48;
    niveau += i;
    ifstream work (niveau.data());
    if(work.is_open())
    {
       string n;
       work >> liste.capacite;
       for(unsigned int k=0;k<liste.capacite;k++)
       {
           work >> n;
           liste.ajouterElement(atoi(n.data()));
       }
       work >> n;
       reussi=atoi(n.data());
       work >> n;
       etoile=atoi(n.data());
       for(int m=0;m<11;m++)
       {
            work >> n;
           fonctionActivee[m]=atoi(n.data());
       }
        work >> nbCoupMax;
        work >> nbEtoilePourDebloquer;
    }
    work.close();
    }

    void niveau::sauveNiveau(int i)
    {
    string niveau="./data/niveau/niveau";
    i += 48;
    niveau += i;
    ofstream work (niveau.data());
    if(work.is_open())
    {
       string n;
       work << liste.capacite <<endl;
       for(unsigned int k=0;k<liste.capacite;k++)
       {
           work << liste.valeurIemeElement(k)<<" ";
       }
       work <<endl;
       work << reussi <<endl;
       work << etoile<<endl;
       for(int m=0;m<11;m++)
       {
            work << fonctionActivee[m]<< " ";
       }
        work << endl;
        work << nbCoupMax<<endl;
        work << nbEtoilePourDebloquer<<endl;
    }
    work.close();
    }

	TableauDynamique * niveau::getListe()
	{
		return &liste;
	}
	TableauDynamique * niveau::getListeTransfert()
	{
		return &listeTransfert;
	}
	int niveau::getReussi() const
	{
		return reussi;
	}
	int niveau::getEtoile() const
	{
		return etoile;
	}
	int niveau::getFonctionActivee(int i) const
	{
		return fonctionActivee[i];
	}
	int niveau::getNbCoupMax() const
	{
		return nbCoupMax;
	}
	int niveau::getNbEtoilePourDebloquer() const
	{
		return nbEtoilePourDebloquer;
	}
	void niveau::setListe(unsigned int i,int val)
	{
		assert(i<=liste.capacite);
		liste.ajouterElement(val);
	}
	void niveau::setListeTransfert(unsigned int i,int val)
	{
		assert(i<=listeTransfert.capacite);
		listeTransfert.ad[i]=val;
	}
	void niveau::setReussi(int reussite)
	{
		reussi=reussite;
	}
	void niveau::setEtoile(int i)
	{
		etoile=i;
	}
	void niveau::setNbCoupMax(int i)
	{
		nbCoupMax=i;
	}
	void niveau::setFonctionActivee(int i,int val)
	{
        fonctionActivee[i]=val;
	}
	void niveau::setNbEtoilePourDebloquer(int val)
	{
	    nbEtoilePourDebloquer=val;
	}
	void niveau::sa(TableauDynamique &tab)
	{
	  int tmp;
	  if(tab.taille_utilisee >= 2)
	  {
		tmp = tab.ad[0];
		tab.ad[0] = tab.ad[1];
		tab.ad[1] = tmp;
	  }
	}

	// sb sa avec tabB
	//ss sa et sb

	void niveau::ss(TableauDynamique &tabA,TableauDynamique &tabB)
	{
	  sa(tabA);
	  sa(tabB);
	}

	void niveau::pa(TableauDynamique &tabA,TableauDynamique &tabB)
	{
	  if(tabA.taille_utilisee != 0)
	  {
		if(tabB.taille_utilisee == 0)
		{
		  tabB.ad[0]=tabA.ad[0];
		  tabB.taille_utilisee =1;
		  tabA.supprimerElement(0);
		}
		else
		{
		  tabB.insererElement(tabA.ad[0],0);
		  tabA.supprimerElement(0);
		}
	  }
	}

	void niveau::ra(TableauDynamique &tab)
	{
	  if(tab.taille_utilisee >= 2)
		{
		  int temp = tab.ad[0];
		  tab.supprimerElement(0);
		  tab.insererElement(temp,tab.taille_utilisee);
		}
	}

	void niveau::rr(TableauDynamique &tabA,TableauDynamique &tabB)
	{
	  ra(tabA);
	  ra(tabB);
	}

	void niveau::rra(TableauDynamique &tab)
	{
	  if(tab.taille_utilisee >= 2)
		{
		  int temp = tab.ad[tab.taille_utilisee-1];
		  tab.supprimerElement(tab.taille_utilisee);
		  tab.insererElement(temp,0);
		}
	}

	void niveau::rrr(TableauDynamique &tabA,TableauDynamique &tabB)
	{
		rra(tabA);
		rra(tabB);
	}
