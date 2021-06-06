#ifndef NIVEAU_H
#define NIVEAU_H

#include <string.h>
#include "TableauDynamique.h"
using namespace std;

class niveau
{
private :
	
	TableauDynamique liste;
	
	TableauDynamique listeTransfert;
	
	int reussi;
	
	int etoile;
	
	int fonctionActivee[11];
	
	int nbCoupMax;
	
	int nbEtoilePourDebloquer;
public :
		
    niveau();
		
    void chargerNiveau(int i);
		
	TableauDynamique * getListe();
	
	TableauDynamique * getListeTransfert();
	int getReussi() const;
	int getEtoile() const;
	int getFonctionActivee(int i) const;
	int getNbCoupMax() const;
	int getNbEtoilePourDebloquer() const;
	void setListe(unsigned int i,int val);
	void setListeTransfert(unsigned int i,int val);
	void setReussi(int reussite);
	void setEtoile(int i);
	void setNbCoupMax(int i);
	void setFonctionActivee(int i,int val);
	void setNbEtoilePourDebloquer(int val);
	void sauveNiveau(int i);

	void sa(TableauDynamique &tab);
	
	void ss(TableauDynamique &tabA,TableauDynamique &tabB);
	
	void pa(TableauDynamique &tabA,TableauDynamique &tabB);
	
	void ra(TableauDynamique &tab);
	
	void rr(TableauDynamique &tabA,TableauDynamique &tabB);
	
	void rra(TableauDynamique &tab);
	
	void rrr(TableauDynamique &tabA,TableauDynamique &tabB);
};


#endif
