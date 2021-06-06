#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
using namespace std;

class Situation
{
private:

	int nbVoitures;
	int voitures[16][4];
	pair<int,int> sortie;
	Situation * parent;
	void creerVoiture(int idVoiture);
	int tableauPositions[6][6]; //Contient les indices de voitures
	
	bool possiblePlacerVoiture();

public:

	~Situation();

	Situation();

	Situation(string nomFichier);

	Situation(const Situation & autre);

	void lireDepuisFichier(string nomFichier);

	void afficher(bool complet=true);

	bool operator== (Situation Acomparer);

	bool estLibre(int voiture, int ligne, int colonne);

	vector<Situation *>& getAutresSituations();

	void deplacerVoiture(int idVoiture, int mouvement);

	int* getVoiture(int idVoiture);

	pair<int,int>& getSortie();

	int getNbVoitures();

	void creerAleatoire();

	string ecrireDansFichier();

	void setParent(Situation * s);

	Situation * getParent();
};
