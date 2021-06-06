#ifndef JEU_H
#define JEU_H

#include <time.h>
#include <ctime>
#include "./Sort.h"
#include "./push_swap.h"
using namespace std;


class jeu
{
    public:
       
        jeu();
       
        virtual ~jeu();

        double GetChronometre() { return chronometre; }
  
        void SetChronometre(double val) { chronometre = val; }
       
        niveau &Getniveau(int j) { return niveaux[j]; }
        
        int GettotalEtoile() { return totalEtoile; }
      
        void SetTotalEtoile(int val) {totalEtoile = val; }

        void InitJeu();

        void SaveJeu();

        int modifChrono(struct tm timer);

        int modifChronograph(struct tm timer);

        void testRegression();

        int verifOrdre(TableauDynamique tab);

        void afficheErreur();

        void afficherAction(TableauDynamique tabA,TableauDynamique tabB,niveau niveau1);

        int test(TableauDynamique tabA,TableauDynamique tabB,int i,struct tm * ttime);

        void afficheHistoire(int i);

        bool jeuAction(TableauDynamique tabA, TableauDynamique tabB,niveau niveau1,int i,int & m);

        void setVp(int niveau,int nbCoup);

        int verifnbCoup(niveau niveau,int nbCoup);

	void aleatoireGen(niveau & niveau1,int n);

    protected:

    private:
        int chronometre;
        niveau niveau1;
        niveau niveau2;
        niveau niveaux[10];
        int totalEtoile; 
};

#endif 
