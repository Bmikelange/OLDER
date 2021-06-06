#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include "../main/jeu.h"
#include "../socklib/bufferedreaderwriter.hpp"

using namespace std;

const size_t TAILLE_BUFF = 100;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
bool verif_bool_function(string verifier_touche, string verifier_string_envoye)
{
  bool check_for_read;
  if (verifier_touche == verifier_string_envoye)
  {
    check_for_read = true;
  }
  else {
    check_for_read = false;

  }
  return check_for_read;
}
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d\n", arr[i]);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int position_of_player(std::vector<int> v, int player)
{
    int pos = 0;
    while(v[pos] != player)
      pos++;
    return (pos + 1);
}
std::string tostr(vector <int> v, int i)
{
    std::stringstream s;
    s << v[i];
    return s.str();
}
int    log ( int socketFD)
{
    struct sockaddr                     address;
    socklen_t                           addressLength = sizeof(address);
    struct sockaddr_in*                 addressInternet;
    string                              ip;
    int                                 port;

    int result = getpeername ( socketFD , &address , &addressLength  );
  //  cout << "Address length is " << addressLength << "     Return is " <<  result << "\n";
    addressInternet = (struct sockaddr_in*)&address;

    ip = inet_ntoa ( addressInternet->sin_addr );
    port = ntohs ( addressInternet->sin_port );

  //  cout << "Socket FD is " << socketFD << " " << ip << ":" << port << " " <<  message << "\n";
  return port;
};
vector <int> toVect(TableauDynamique tab)
{
  vector <int> v;
  for(int i = 0; i < tab.taille_utilisee; i++)
  {
    v.push_back(tab.valeurIemeElement(i));
  }
  return v;
}
bool is_num(char * str_num)
{
  bool verif =  true;
  int i = 0;
  while (str_num[i] != '\n')
  {
    if (!isdigit(str_num[i]))
    {
      verif = false;
      break;
    }
    i++;
  }
  return verif;
}
int number_from_string(char * str)
{
  char * nr_string;
  int nr;
  int i = 0;

  while ((nr_string = strchr(str, ' ')) != NULL)
  {
    nr_string++;
    if(is_num(nr_string))
      break;
    else
      str = nr_string;
  }
  nr = atoi(nr_string);
  return nr;
}
int main(int argc, char *argv[]) {

    string port;
    pid_t pid;
    int fd;
    //count_ins = 8;

    // on teste le nombre d'arguments.
    // Attention, il y a toujours le nom du programme donc argc==
    // signifie un argument.
      port = argv[1];

      cerr << "Je suis serveur sur le port " << port << endl;
    if(argc != 2) {
        cerr << "usage " << argv[0] << " <port> : pour le serveur" << endl;
        exit(1);
    }
    string ligne;
    std::vector<int> ports(2,0);

    int s_serv = socklib::CreeSocketServeur(port);
    while(1)
    {
        // #########################
        // code du serveur
        // #########################

        // création de la socket d'écoute

        // attente d'un nouveau client
        size_t size_mess = 50;
        int s = socklib::AcceptConnexion(s_serv);

        if (s != -1)
        {
          cout << log(s) << endl;
            ports.push_back(log(s));
            cout << ports[0] << endl;
            int status, myPipe[2];
            pipe(myPipe);  // create the pipe
            pid =  fork();
            if (pid == -1)
            {
                printf("%s\n", "exit_error");
            }
            if(pid == 0)
            {
                fd = open("./data/serveur/leader_board.txt",O_RDWR);
                socklib::BufferedReaderWriter rw(fd);
                socklib::BufferedReaderWriter rw2(s);
                string str_to_compare = "leader\n";
                string string_checker = rw2.read_line();
                cout << string_checker << endl;

                bool chose_task = verif_bool_function(str_to_compare, string_checker);
                cout << "val bool " << chose_task << endl;
                if (chose_task == true)
                {
                  char test='\n';
                  while (true) {
                      char  mess[50];
                      bzero(&mess,50);
                      int res = recv(s, &mess,50, 0);
                      printf("%s\n",mess );

                      exit_error("serveur : lecture sur la socket", res == -1, errno);
                      cout << mess << endl;
                      if (res == 1 && mess[0]=='\n') {
                          cout << "fermeture de la connexion"  << endl;
                          break;
                      }
                      mess[strlen(mess)] = '\n';
                      int nr_from_mess = number_from_string(mess);
                  //    printf("nr form mess = %d\n", nr_from_mess);
                  /*    if (nr_from_mess >= count_ins)
                      {
                        lseek(fd,0, SEEK_CUR);
                      }
                      else*/
                      lseek(fd,0, SEEK_END);
                      write(fd,&mess,strlen(mess));
                  }
                  lseek(fd,0,SEEK_SET);
                  std::vector<int> tab_values;
                  std::vector<std::string> strVec;
                  string tab[10];
                  while (true) {
                      ligne = rw.read_line();
                      if (ligne == "") {
                          //ligne="\n";
                          //rw2.write(ligne);
                          break;
                      }
                      strVec.push_back(ligne);
                      char * nr = (char *)ligne.c_str();
                      int nr1  =  number_from_string(nr);
                      tab_values.push_back(nr1);

                    //   cout << "> " << ligne << endl;
                  }
                  int last_player = tab_values[tab_values.size() - 1];

                  int n = tab_values.size();
                  //array sorted
                  quickSort(tab_values.data(), 0, n - 1);
                  //reverse array
                //  reverse(tab_values.begin(), tab_values.end());

                  int pos_player = position_of_player(tab_values, last_player);
                  if (pos_player > 10)
                      printf("position de player : %d\n", pos_player);
                  //printArray(tab_values.data(), n);
                  //printf("%s\n", "to send::");
                  for(int i  = 0; i < strVec.size(); i++)
                    //std::cout << strVec[i] << '\n';
                  for(int j = 0; j < strVec.size(); j++)
                  {
                      for (int i = 0; i < 10; i++)
                      {
                          string first_ten = tostr(tab_values, i);
                          std::size_t found = strVec[j].find(" "+first_ten);
                          if (found!=std::string::npos)
                          {
                              if(tab[i]=="")
                              {
                                  tab[i]=strVec[j];
                                  i=11;
                              }

                          }
                      }
                  }
                  for(int w=0;w<10;w++)
                  {
                      rw2.write(tab[w]);
                      cout<<tab[w]<<endl;
                  }
                  string nr_of_players = to_string(strVec.size());
                  string t="\n";
                  rw2.write(t);
                  sleep(2);
                  rw2.write(to_string(pos_player)+" / "+nr_of_players+"\n");
                }
                else{
                  int fd_liste = open("./data/serveur/liste.txt",O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
                  socklib::BufferedReaderWriter rw_file(fd_liste);

                  string check_if_empty = rw_file.read_line();

                  //std::vector<int> v_port;
                  //cout << log(s) << endl;
                  //v_port.push_back(log(s));
                  // read string to check which value asign to bool
                    TableauDynamique * A;
                    jeu j;
                    niveau n;
                    string liste;;

                    //std::vector<int> v_port;
                    //cout << log(s) << endl;
                    //v_port.push_back(log(s));
                    // read string to check which value asign to bool

                  if(check_if_empty == "")
                  {
                    j.aleatoireGen(n,4);
                    A=n.getListe();
                    A->afficher();

                    vector <int> liste_vector = toVect(*A);
                    for(int i = 0; i < A->taille_utilisee; i++)
                    {
                      liste += tostr(liste_vector, i) + "\n";
                    }
                    cout <<"liste: " <<  liste << endl;
                    rw_file.write(liste);
                    rw_file.write("end\n");

                  }

                  string send_liste;
                  lseek(fd_liste,0,SEEK_SET);
                  rw_file.write("0\n");


                  while((send_liste=rw_file.read_line()) != "")
                  {
                    rw2.write(send_liste);

                    if(send_liste == "end\n")
                      break;
                  }
                  cout << "yyyyyyyyyyyy" << endl;
                  string test="\n";
                  rw_file.close();

                  int i=0;
                  string tabScore[2];
                  string lScore="    ";
                  lScore=rw2.read_line();
                  cout<<lScore<<endl;
                  int fd_test;
                  int t;
                  if((fd_test=open("./data/joueur1.txt",O_RDWR))<0)
                  {
                    fd_test=open("./data/joueur1.txt",O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
                    socklib::BufferedReaderWriter rw_test(fd_test);
                    t=1;
                    cout<<"joueur1 créé"<<endl;
                    rw_test.write(lScore);
                    rw_test.close();
                  }
                  else
                  {
                    fd_test=open("./data/joueur2.txt",O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
                    socklib::BufferedReaderWriter rw_test(fd_test);
                    t=2;
                    cout<<"joueur2 créé"<<endl;
                    rw_test.write(lScore + "\n");
                    rw_test.close();
                  }
                  int fd_lec;
                  cout<<"joueur test"<<endl;
                  while((fd_lec=open("./data/joueur2.txt",O_WRONLY))<0)
                  {
                    sleep(5);
                    rw2.write("5\n");
                  }
                  rw2.write("\n");
                  cout<<"joueur créé"<<endl;
                  close(fd_lec);
                  tabScore[0]=lScore;
                  int fd_tr;
                  if(t==1)
                  {
                    cout<<"joueur nu1"<<endl;
                    fd_tr=open("./data/joueur2.txt",O_RDWR);
                    socklib::BufferedReaderWriter rw_lec(fd_tr);
                    tabScore[1]=rw_lec.read_line();
                    cout<< "mon "<<tabScore[0] <<"ton "<< tabScore[1] << endl;
                    rw_lec.close();
                    remove("./data/joueur2.txt");
                  }
                  if(t==2)
                  {
                    cout<<"joueur nu2"<<endl;
                    fd_tr=open("./data/joueur1.txt",O_RDWR);
                    socklib::BufferedReaderWriter rw_lec(fd_tr);
                    tabScore[1]=rw_lec.read_line();
                    cout<< "mon "<<tabScore[0] <<"ton "<< tabScore[1] << endl;
                    rw_lec.close();
                    remove("./data/joueur1.txt");
                  }
                  if(tabScore[0]< tabScore[1] )
                  {
                    lScore="1\n";
                  }
                  else{
                    lScore="0\n";
                  }
                  remove("./data/serveur/liste.txt");
                  cout<<"ecrit la "<< lScore<<endl;
                  rw2.write(lScore);
                }
                  //    cout << first_ten << "\n" << endl;
                  rw.close();
                  close (s_serv);
                  rw2.close();
            }
        }
        // la lecture que je fait là n'est pas très propre,
        // il faudra l'améliorer.
    }


    return 0;
}
