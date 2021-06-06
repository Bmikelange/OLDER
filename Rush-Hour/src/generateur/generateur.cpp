#include <iostream>
#include "../resolveur/Superviseur.h"
#include <cstdlib>
using namespace std;

#define NB_COUPS_MIN 10

void traitement_main(int argc, char ** argv, int & b)
{
	if(argc > 3)
	{
		cerr<<"Utilisation : "<<endl;
		cerr<<argv[0]<<" [Nombre de coups minimum]"<< " (-t)"<<endl;
		cerr<<"-t -- utilise du multithread"<<endl;
		cerr<<"Le nombre de coups minimum par defaut est de ";
		cerr<<NB_COUPS_MIN<<endl;
		exit(0);
	}
	b = NB_COUPS_MIN;
	if(argc>=2 && argc <=3){
		try
		{
			b = stoi(argv[1]);
		}
		catch (const invalid_argument& ia)
		{
			cerr<<"Utilisation : "<<endl;
			cerr<<argv[0]<<" [Nombre de coups minimum]"<<" (-t)"<<endl;
			cerr<<"-t -- utilise du multithread"<<endl;
			cerr<<"Le nombre de coups minimum par defaut est de ";
			cerr<<NB_COUPS_MIN<<endl;
			exit(0);
		}
		if (argv[2] && argv[2] != string("-t"))
		{
			cerr<<"Utilisation : "<<endl;
			cerr<<argv[0]<<" [Nombre de coups minimum]"<<" (-t)"<<endl;
			cerr<<"-t -- utilise du multithread"<<endl;
			cerr<<"Le nombre de coups minimum par defaut est de ";
			cerr<<NB_COUPS_MIN<<endl;
			exit(0);
		}
	}
}

int main(int argc, char ** argv)
{
	srand(time(NULL));
	int borneMin;
	traitement_main(argc,argv,borneMin);
	int difficulte = 0;
	Situation * s = nullptr;
	streambuf * backup = cout.rdbuf();
	cout<<"Creation d un puzzle de difficulte "<<borneMin<<endl;
	do
	{
		delete s;
		s = new Situation();
		cout<<"Creation aleatoire"<<endl;
		s->creerAleatoire();
		Superviseur sup(*s,argc);
		//cout<<"Resolution"<<endl;
		//s.afficher();
		cout.rdbuf(NULL); //Enlever l'affichage en détachant le buffer de cout
		difficulte = sup.resolution();
		cout.rdbuf(backup); //Rétablir l'affichage
		cout<<"Resolution terminee d'un puzzle de difficulte "<<difficulte<<endl;
	}
	while(difficulte < borneMin);
	s->afficher();
	cout<<"Puzzle de difficulte : "<<difficulte<<endl;
	string str = s->ecrireDansFichier();
	cout<<"Puzzle sauvegarde dans : "<<str<<endl;
	delete s;
	return 0;
}
