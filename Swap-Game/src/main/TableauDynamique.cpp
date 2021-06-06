#include "TableauDynamique.h"

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

TableauDynamique::TableauDynamique () {
    ad = new ElementTD [1];
    capacite = 1;
    taille_utilisee = 0;
}

TableauDynamique::TableauDynamique (const TableauDynamique & t) {
  ad = new ElementTD [t.capacite];
  capacite = t.capacite;
  taille_utilisee = t.taille_utilisee;
  for (unsigned int i = 0; i < t.taille_utilisee; i++) ad[i] = t.ad[i];
}

TableauDynamique::~TableauDynamique () {
  if (ad == NULL) {
	delete [] ad;
	ad = NULL;
  }
  capacite = 0;
  taille_utilisee = 0;
}

void TableauDynamique::vider () {
  if (ad == NULL) delete [] ad;
  ad = new ElementTD [1];
  capacite = 1;
  taille_utilisee = 0;
}

void TableauDynamique::ajouterElement (ElementTD e) {
  ElementTD * temp;
  if (taille_utilisee == capacite) { // tableau plein, doublons la capacité
      temp = ad;
      ad = new ElementTD [capacite + 1];
      if(ad == NULL) {
          cout << "Espace memoire insuffisant" << endl;
          exit(EXIT_FAILURE);
      }
      capacite += 1;
      for (unsigned int i = 0; i < taille_utilisee; i++) ad[i] = temp[i];
      delete [] temp;
  }
  ad[taille_utilisee] = e;
  taille_utilisee++;
}

ElementTD TableauDynamique::valeurIemeElement (unsigned int indice) const {
  return ad[indice];
}

void TableauDynamique::modifierValeurIemeElement (ElementTD e, unsigned int indice) {
  ad[indice] = e;
}

void TableauDynamique::afficher () const {
  for (unsigned int i = 0; i < taille_utilisee; i++) {
        afficheElementTD(ad[i]);
        cout << " ";
  }
  cout << endl;
}

void TableauDynamique::supprimerElement (unsigned int indice) {
  if(indice < taille_utilisee-1) {
      for(unsigned int p = indice; p < taille_utilisee-1; p++)
        ad[p] = ad[p+1];
  }
  taille_utilisee--;
    ElementTD * temp = &ad[0];
    capacite = capacite--;
    ad = new ElementTD [capacite];
    for(unsigned int p = 0; p < taille_utilisee; p++)
        ad[p] = temp[p];
    delete [] temp;
}

void TableauDynamique::insererElement (ElementTD e, unsigned int indice) {
  if(taille_utilisee > 0) {
      /* S'il y a au moins un ElementTD dans le tableau, on recopie le dernier
         en appelant la procédure d'ajout, qui s'occupera d'augmenter la capacité si nécessaire */
      ajouterElement(ad[taille_utilisee - 1]);
  }
  /* Ensuite on décale d'un cran les éléments à droite de indice */
  for (unsigned int j = taille_utilisee - 1; j > indice; j--)
    ad[j] = ad[j-1];
  /* On peut enfin insérer e à la position indice */
  ad[indice] = e;
}

/*void TableauDynamique::trier () {
  unsigned int i, j, indmin;
  ElementTD min;
  for (i = 0; i < taille_utilisee - 1; i++) {
      indmin = i;
      for (j = i+1; j < taille_utilisee; j++) {
          if (ad[j] < ad[indmin]) indmin = j;
      }
      min = ad[indmin];
      ad[indmin] = ad[i];
      ad[i] = min;
    }
}
*/
int TableauDynamique::rechercherElement (ElementTD e) const {
       int res =-1;
       for(int i=0;i<taille_utilisee;i++)
       {
         if(ad[i]==e)
         {
           res=e;
         }
      }
    return res;
}

std::string TableauDynamique::TDtoString() {
    std::string list = "";

	for (unsigned int i = 0; i < taille_utilisee ; i++) {
		list += to_string(valeurIemeElement(i));
		list += " "; 					   	//nombres d'espaces entre les nombres de la liste
	}

	return list;
}
