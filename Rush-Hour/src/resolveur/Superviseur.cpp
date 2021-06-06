#include "Superviseur.h"
#include <cstdlib>
#include <unistd.h>
#include <stack>

Superviseur::Superviseur(string nomFichier,int thread)
{
	situationInitiale=new Situation(nomFichier);
	nbThreads=thread::hardware_concurrency();
	for(int i=0;i<8000000;i++)
	{
		tableauSituation[i]=false;
	}
	if(nbThreads==0 || thread==0)
	{
		nbThreads=1;
	}
}

Superviseur::Superviseur(const Situation & s,int thread)
{
	situationInitiale = new Situation(s);
	nbThreads=thread::hardware_concurrency();
	for(int i=0;i<8000000;i++)
	{
		tableauSituation[i]=false;
	}
	if(nbThreads==0 || thread!=3)
	{
		nbThreads=1;
	}
}

int Superviseur::hashageSituation(Situation * s)
{
	int hash=0;
	for(int i=0;i<s->getNbVoitures();i++)
	{
		string temp="";
		temp=temp+to_string(i);
		if(i%6==0)
		{
			temp=temp+to_string(6*stoi(temp)*s->getVoiture(i)[0]);
			temp=temp+to_string(s->getVoiture(i)[1]);
			hash+=11*stoi(temp);
		}
		else if(i%2==0)
		{
			temp=temp+to_string(stoi(temp)*s->getVoiture(i)[0]);
			temp=temp+to_string(s->getVoiture(i)[1]);
			hash+=4*stoi(temp);
		}
		else if(i%3==0)
		{
			temp=temp+to_string(s->getVoiture(i)[0]);
			temp=temp+to_string(stoi(temp)*s->getVoiture(i)[1]);
			hash+=9*stoi(temp);
		}
		else if(i%7==0)
		{
			temp=temp+to_string(7*s->getVoiture(i)[0]);
			temp=temp+to_string(7*s->getVoiture(i)[1]);
			hash+=12*stoi(temp);
		}
		else	
		{
			temp=temp+to_string(s->getVoiture(i)[0]);
			temp=temp+to_string(stoi(temp)*s->getVoiture(i)[1]);
			hash+=stoi(temp);
		}
	}
	return hash;
}

bool Superviseur::mouvementEstPossible(Situation * s, int v, int m)
{
	int * voiture = s->getVoiture(v);
	int sens = voiture[3];
	bool test = (voiture[sens] + m >= 0 && voiture[sens] + m < 6);
	if(!test)
	{
		return test;
	}
	int debut = (m >= 0 ? voiture[2]-1 : m);
	int fin = (m >= 0 ? debut + m : 0);
	for(int i = debut ; i <= fin ; i++)
	{
		int ligne = voiture[0];
		int colonne = voiture[1];
		if(sens == 1)
		{
			colonne += i;
		}
		else
		{
			ligne += i;
		}
		test = test && s->estLibre(v,ligne,colonne);
	}
	return test;
}

bool Superviseur::estGagnante(Situation * s)
{
	int * voiture = s->getVoiture(0);
	int sens = voiture[3];
	pair<int,int> sortie = s->getSortie();
	int caseSortie = (sens == 0 ? sortie.first : sortie.second);
	return (voiture[sens] + voiture[2]-1 == caseSortie);
}


//Renvoie un strig contenant le coup qui a été effectué pour passer de s1 à s2
//Précondition : l'appeler sur deux situations séparées par un coup uniquement !
static string coup(Situation * s1, Situation * s2)
{
	string s = "";
	for(int i = 0 ; i < s1->getNbVoitures() ; i++)
	{
		int indice = s1->getVoiture(i)[3];
		if(s1->getVoiture(i)[indice] != s2->getVoiture(i)[indice])
		{ 
			s = s + to_string(i) + " : " + to_string(s1->getVoiture(i)[indice]) + "->" + to_string(s2->getVoiture(i)[indice]);
		}
	}
	return s;
}


void Superviseur::traitement()
{
	Situation * s = nullptr;
	do
	{
		mNbSit.lock();
		if(verif > 0)
		{
			s = situationsATraiter.front();
			situationsATraiter.pop();
			verif--;
		}
		else
		{
			mNbSit.unlock();
			break;
		}
		mNbSit.unlock();
		for(int v = 0 ; v < s->getNbVoitures() ; v++)
		{
			bool test;
			int m = 1;
			do
			{
				test = false;
				if(mouvementEstPossible(s,v,m))
				{
					creerSituation(s,v,m);
					test = true;
				}
				if(mouvementEstPossible(s,v,-m))
				{
					creerSituation(s,v,-m);
					test = true;
				}
				m++;
			}
			while(test);
		}
		lockverif.lock();
		if(!estGagnante(s))
		{
			situationsTraitees.push_back(s);
		}		
		else
			finir=true;
		lockverif.unlock();
		lock.lock();
		nbSitTraitees=nbSitTraitees+1;
		lock.unlock();
	}
	while(!situationsATraiter.empty() && !finir);
	if(s != nullptr && estGagnante(s))
	{
		lockverif.lock();
		cout<<"Nombre de coups necessaires au minimum : "<<nbCoups<<endl;
		cout<<"Nombre total de situations traitees : "<<nbSitTraitees<<endl;
		cout<<"Nombre de threads maximum utilisés : "<<nbThreads<<endl<<endl;
		Situation* temp=s;
		stack<Situation *> parentBonOrdre;
		while(temp != nullptr)
		{
			parentBonOrdre.push(temp);
			temp=temp->getParent();
		}
		parentBonOrdre.top()->afficher();
		while(parentBonOrdre.size() > 1)
		{
			Situation * parent = parentBonOrdre.top();
			parentBonOrdre.pop();
			cout<<coup(parent, parentBonOrdre.top())<<endl<<endl;
			parentBonOrdre.top()->afficher(false);
		}
		delete(s);
		lockverif.unlock();
	}

}

int Superviseur::resolution()
{
	cout<<"Resolution du puzzle en cours..."<<endl;
	finir = false;
	situationsATraiter.push(situationInitiale);
	do
	{
		vector<thread> tableThreads;
		verif = situationsATraiter.size();
		for(unsigned int i=0;i<nbThreads;i++)
		{
			tableThreads.push_back(thread(&Superviseur::traitement,this));
		}
		for(unsigned int i=0;i<nbThreads;i++)
		{
			tableThreads[i].join();
		}
		nbCoups++;
	}
	while(!finir && situationsATraiter.size() > 0);
	return (situationsATraiter.size() == 0 ? -1 : nbCoups-1);
}


void Superviseur::creerSituation(Situation * s, int v, int m)
{
	Situation * n = new Situation(*s);
	n->deplacerVoiture(v,m);
	lock.lock();
	int indice=hashageSituation(n);
	if(tableauSituation[indice])
	{
		delete n;
	}
	else
	{	
		n->setParent(s);
		situationsATraiter.push(n);
		tableauSituation[indice]=true;
	}
	lock.unlock();
}


Superviseur::~Superviseur()
{
	while(!situationsATraiter.empty())
	{
		delete(situationsATraiter.front());
		situationsATraiter.pop();
	}
	while(situationsTraitees.size()!=0)
	{
		delete(situationsTraitees[situationsTraitees.size()-1]);
		situationsTraitees.erase(situationsTraitees.end()-1);
	}
	
}
