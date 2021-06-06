#pragma once
#include "Situation.h"
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>


class Superviseur{
private:

	Situation* situationInitiale;
	queue<Situation *> situationsATraiter;
	vector<Situation *> situationsTraitees;
	unsigned int nbThreads;
	
	mutex lock;
	mutex lockverif;
	mutex mNbSit;
	int nbSitTraitees = 0;
	int nbCoups=0;
	unsigned int verif=0;
	int compteur=0;
	bool finir;
	condition_variable controlThread;
	bool tableauSituation[8000000];

	//v : id de la voiture, m : mouvement (de combien de cases on bouge)
	bool mouvementEstPossible(Situation * s, int v, int m);

	//Verifie si la situation passée en paramètre est gagnante
	bool estGagnante(Situation * s);

	//Permet de créer une nouvelle situation à partir de celle passée
	//en paramètre où la voiture v a subi le mouvement m
	void creerSituation(Situation * s, int v, int m);

	//Donnes un identifiant unique à chaque situation
	int hashageSituation(Situation * s);

	//execute les fonctions de création de situations à partir d'une situation données
	void traitement();

public:

	~Superviseur();
	Superviseur(string nomFichier,int thread);
	Superviseur(const Situation & s,int thread);
	int resolution();
};
