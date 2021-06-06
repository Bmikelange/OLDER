#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>

#include "./client.h"
#include "../main/TableauDynamique.h"

using namespace std;

const size_t TAILLE_BUFF = 100;

int s=-1;
socklib::BufferedReaderWriter rw(1);


int gere_client(string adresse,string port,string info,string tab[10],string & n,bool i,TableauDynamique & A,int & nbCoup) {
  // on teste le nombre d'arguments.
  // Attention, il y a toujours le nom du programme donc argc==
    // #########################
    // Code du client
    // #########################
    static int ingame=0;
    string verif_bool;
    if(ingame==0)
      {
      s = socklib::CreeSocketClient(adresse, port);
      socklib::BufferedReaderWriter temp(s);
      std::swap(rw, temp);

      if (i==1)
      {
        verif_bool="leader\n";
      }
      else
      {
        verif_bool="multi\n";
      }
      rw.write(verif_bool);
        // j'utilise getline pour lire plus d'un mot (>> s'arrete
        // au premier espace)
      if(i==1)
      {
        int res2 = send(s, info.data(), info.size(), 0);
        sleep(2);
        string test="\n";
        int res = send(s,test.data(), test.size(), 0);
        cout << "fin"<<endl;
        int i=0;
        while (true) {
          string t = rw.read_line();

          if (t == "\n") {
               cout << "Fermeture de la connexion"  << endl;
                break;
          }
          tab[i]=t;
          i++;
        }
        string tempo=rw.read_line();
        n=tempo;
        //shutdown(s,2);
        rw.close();
    }
    else{
      string ligne;
      while (true)
      {

        // j'utilise getline pour lire plus d'un mot (>> s'arrete
        // au premier espace)

        ligne = rw.read_line();

        if (ligne == "end\n")
        {
            //ligne="\n";
          //  rw.write(ligne);
            break;
        }
        A.ajouterElement(atoi(ligne.c_str()));

        cout << ligne << endl;


      }

      A.afficher();

        // j'utilise getline pour lire plus d'un mot (>> s'arrete
        // au premier espace)
        /*getline(cin, mess);

        if (mess == "fin") {
          mess="\n";

          int res2 = send(s, mess.data(), mess.size(), 0);
          exit_error("client : envoie sur la socket", res2 == -1, errno);
           cout << "fermeture de la connexion"  << endl;
        }*/
        //rw.write("\n");
        ingame=1;
    }
      // fermeture marche pas , a voir apres , ca peut causer des problemes
    // close(s);
    //shutdown(s,2);

    return 0;
  }
  else
  {
    rw.write(to_string(nbCoup)+"\n");
    string ligned;
    while(true)
    {
      string tempo;
      tempo=rw.read_line();
      if(tempo=="\n")
        break;
      sleep(atoi(tempo.c_str()));
    }
    int i=0;
    ligned=rw.read_line();
    nbCoup=atoi(ligned.c_str());
    cout<<nbCoup<<endl;
    ingame=0;
    rw.close();
  }
  return 0;
}
