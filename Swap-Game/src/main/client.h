#include "../socklib/bufferedreaderwriter.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <strings.h>
#include "TableauDynamique.h"
using namespace std;

int gere_client(string adresse,string port,string info,string tab[10],string & n,bool i,TableauDynamique & A,int &nbCoup);
