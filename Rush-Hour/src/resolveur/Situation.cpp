#include "Situation.h"
#include <fstream>
#include <sstream>

Situation::Situation()
{
	//cout<<"Constructeur de situation"<<endl;
	sortie.first = 2;
	sortie.second = 5;
	nbVoitures = 1;
	voitures[0][0] = 2;
	voitures[0][1] = 0;
	voitures[0][2] = 2;
	voitures[0][3] = 1;
	for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 6 ; j++)
		{
			tableauPositions[i][j] = -1;
		}
	}
	parent=nullptr;
	for(int i = 0 ; i < voitures[0][2] ; i++)
	{
		int ligne = (1-voitures[0][3]) * i + voitures[0][0];
		int colonne = voitures[0][3] * i + voitures[0][1];
		tableauPositions[ligne][colonne] = 0;
	}
}

Situation::Situation(const Situation & autre)
{
	Situation();
	parent=autre.parent;
	sortie.first = autre.sortie.first;
	sortie.second = autre.sortie.second;
	nbVoitures = autre.nbVoitures;
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
		{
			voitures[i][j] = autre.voitures[i][j];
		}
	}
	for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 6 ; j++)
		{
			tableauPositions[i][j] = autre.tableauPositions[i][j];
		}
	}
}

Situation::Situation(string nomFichier)
{
	Situation();
	lireDepuisFichier(nomFichier);
}

void Situation::lireDepuisFichier(string nomFichier)
{
	for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 6 ; j++)
		{
			tableauPositions[i][j] = -1;
		}
	}
	ifstream is(nomFichier);
	if(!is.is_open())
	{
		cerr<<"Fichier non trouve"<<endl;
		exit(1);
	}
	string s;
	int nbLigne = 0;
	int i = 0;
	while(!is.eof())
	{
		if(nbLigne == 0)
		{
			is >> sortie.first;
			is >> sortie.second;
			nbLigne++;
		}
		else
		{
			is >> voitures[i][0];
			is >> voitures[i][1];
			is >> voitures[i][2];
			is >> voitures[i][3];
			int sens = voitures[i][3];
			for(int j = 0 ; j < voitures[i][2] ; j++)
			{
				int ligne = voitures[i][0];
				int colonne = voitures[i][1];
				if(sens == 0)
				{
					ligne += j;
				}
				else
				{
					colonne += j;
				}
				tableauPositions[ligne][colonne] = i;
			}
			i++;
		}
	}
	nbVoitures = i;
	is.close();
}

void Situation::afficher(bool complet)
{
	if(complet)
	{
		cout<<"Coordonnees de la sortie : "<<sortie.first<<" "<<sortie.second<<endl;
		cout<<"Voiture a sortir : "<<voitures[0][0]<<" "<<voitures[0][1]<<" "
			<<voitures[0][2]<<" "<<voitures[0][3]<<endl;
		for(int i = 1 ; i < nbVoitures ; i++)
		{
			cout<<"Voiture "<<i<<" : "<<voitures[i][0]<<" "<<voitures[i][1]<<" "
				<<voitures[i][2]<<" "<<voitures[i][3]<<endl;
		}
		cout<<endl;
	}
	for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 6 ; j++)
		{
			if(tableauPositions[i][j] == -1)
			{
				cout<<" ";
			}
			else
			{
				cout<<std::hex<<tableauPositions[i][j]<<std::dec;
			}
		}
		cout<<endl;
	}
	cout<<endl;
}

bool Situation::operator== (Situation Acomparer)
{
    for( int i=0;i<nbVoitures;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(voitures[i][j] != Acomparer.voitures[i][j])
               return false;
        }
    }
    return true;
}

Situation::~Situation()
{
}

bool Situation::estLibre(int voiture, int ligne, int colonne)
{
	return ((ligne >= 0 && ligne < 6 &&
			colonne >= 0 && colonne < 6) &&
			(tableauPositions[ligne][colonne] == -1 ||
			tableauPositions[ligne][colonne] == voiture));
}


void Situation::deplacerVoiture(int idVoiture, int mouvement)
{
	int sens = voitures[idVoiture][3];
	for(int i = 0 ; i < voitures[idVoiture][2] ; i++)
	{
		int ligne = voitures[idVoiture][0];
		int colonne = voitures[idVoiture][1];
		if(sens == 0)
		{
			ligne += i;
		}
		else
		{
			colonne += i;
		}
		tableauPositions[ligne][colonne] = -1;
	}
	voitures[idVoiture][sens] += mouvement;
	for(int i = 0 ; i < voitures[idVoiture][2] ; i++)
	{
		int ligne = voitures[idVoiture][0];
		int colonne = voitures[idVoiture][1];
		if(sens == 0)
		{
			ligne += i;
		}
		else
		{
			colonne += i;
		}
		tableauPositions[ligne][colonne] = idVoiture;
	}
}

int* Situation::getVoiture(int idVoiture)
{
	return voitures[idVoiture];
}

pair<int,int>& Situation::getSortie()
{
	return sortie;
}

int Situation::getNbVoitures()
{
	return nbVoitures;
}

void Situation::creerVoiture(int idVoiture)
{
	bool test;
	do
	{
		test = true;
		//Une voiture ne peut pas commencer en (6,6)
		do
		{
			voitures[idVoiture][0] = rand() % 6;
			voitures[idVoiture][1] = rand() % 6;
			//cout<<"Coordonnees : "<<voitures[idVoiture][0]<<" "<<voitures[idVoiture][1]<<endl;
		}
		while(voitures[idVoiture][0] == 5 && voitures[idVoiture][1] == 5);
		if(voitures[idVoiture][0] == 5)
		{
			voitures[idVoiture][3] = 1;
		}
		else if(voitures[idVoiture][1] == 5)
		{
			voitures[idVoiture][3] = 0;
		}
		else
		{
			voitures[idVoiture][3] = rand() % 2;
		}
		
		// On détermine la longueur de la voiture
		// en fonction de l'espace restant
		do
		{
			voitures[idVoiture][2] = rand() % 2 + 2;
		}
		while(voitures[idVoiture][2] - 1
		+ (1-voitures[idVoiture][3]) * voitures[idVoiture][0]
		+ voitures[idVoiture][3] * voitures[idVoiture][1] >= 6);
		//afficher();
		//cout<<"Voiture : "<<voitures[idVoiture][0]<<" "<<voitures[idVoiture][1]<<" "<<voitures[idVoiture][2]<<endl;
		//On vérifie si les cases sont occupées
		for(int i = 0 ; i < voitures[idVoiture][2] ; i++)
		{
			test = test && estLibre(idVoiture,
				(1-voitures[idVoiture][3]) * i + voitures[idVoiture][0],
				voitures[idVoiture][3] * i + voitures[idVoiture][1]);
		}
		test = test && !(voitures[idVoiture][3] == 1 && voitures[idVoiture][0] == 2);
		//cout<<"Test : "<<test<<endl;
	}
	while(!test);
	for(int i = 0 ; i < voitures[idVoiture][2] ; i++)
	{
		int ligne = (1-voitures[idVoiture][3]) * i + voitures[idVoiture][0];
		int colonne = voitures[idVoiture][3] * i + voitures[idVoiture][1];
		tableauPositions[ligne][colonne] = idVoiture;
	}
}

void Situation::creerAleatoire()
{
	sortie.first = 2;
	sortie.second = 5;
	nbVoitures = 1;
	voitures[0][0] = 2;
	voitures[0][1] = 0;
	voitures[0][2] = 2;
	voitures[0][3] = 1;
	for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 6 ; j++)
		{
			tableauPositions[i][j] = -1;
		}
	}
	for(int i = 0 ; i < voitures[0][2] ; i++)
	{
		int ligne = (1-voitures[0][3]) * i + voitures[0][0];
		int colonne = voitures[0][3] * i + voitures[0][1];
		tableauPositions[ligne][colonne] = 0;
	}
	nbVoitures = rand() % 15 + 2;
	int i = 1;
	do
	{
		//cout<<"Creer voiture "<<i<<endl;
		creerVoiture(i);
		i++;
	}
	while(i < nbVoitures && possiblePlacerVoiture());
	if(!possiblePlacerVoiture())
	{
		nbVoitures = i;
	}
}

string Situation::ecrireDansFichier()
{
	stringstream ss;
	int i = 0;
	ifstream is("data/1");
	do
	{
		is.close();
		ss.str("");
		ss<<"data/"<<i;
		is.open(ss.str());
		i++;
	}
	while(is.is_open());
	
	ofstream os(ss.str());
	if(!os.is_open())
	{
		cerr<<"Erreur lors de la tentative d'ecriture de ";
		cerr<<"la situation dans le fichier "<<ss.str()<<endl;
		exit(0);
	}
	os << sortie.first << " ";
	os << sortie.second << '\n';
	for(int i = 0 ; i < nbVoitures ; i++)
	{
		os << voitures[i][0] << " ";
		os << voitures[i][1] << " ";
		os << voitures[i][2] << " ";
		os << voitures[i][3] << '\n';
	}
	return ss.str();
}

bool Situation::possiblePlacerVoiture()
{
	for(int i = 0 ; i < 5 ; i++)
	{
		for(int j = 0 ; j < 5 ; j++)
		{
			if(estLibre(-1,i,j))
			{
				if((i+1 < 5 && estLibre(-1,i+1,j)) || 
				(j+1 < 5 && estLibre(-1,i,j+1) && i != 2))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Situation::setParent(Situation * s)
{
	parent=s;
}

Situation * Situation::getParent()
{
	return parent;
}
