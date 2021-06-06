#include <iostream>
#include "Superviseur.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2 || argc > 3)
	{
		cerr<<"Utilisation : "<<endl;
		cerr<<argv[0]<<" [Chemin du fichier a resoudre]"<< " (-t)"<<endl;
		cerr<<"-t -- utilise du multithread"<<endl;
		exit(0);
	}
	else
	{
		if(argc==2)
		{
			Superviseur sup(argv[1],0);
			sup.resolution();
			return 0;
		}
		if(argv[2] && argv[2] != string("-t"))
		{
			Superviseur sup(argv[1],0);
			sup.resolution();
		}		
		else
		{
			Superviseur sup(argv[1],1);
			sup.resolution();
		}
	}
	return 0;
}
