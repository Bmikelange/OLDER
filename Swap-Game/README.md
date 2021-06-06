
Commande de compilatoin : make test exemple sdl serveur 

Regles de jeu:

   • Le jeu est constitué de 2 piles nommées a et b.

• Au départ :


   ◦ a contient un nombre arbitraire d’entiers positifs ou négatifs, sans doublons.

   ◦ b est vide

• Le but du jeu est de trier a dans l’ordre croissant.

• Pour ce faire, on ne dispose que des opérations suivantes :
	
	SA(swap a), SB(swap b), SS(SA + SB), RA(push a), PB(push b), RA(rotate a), RB(rotate b), RR(RA + RB)
			    RRA(reverse rotate a), RRB(reverse rotate b), RRR(RRA + RRB)

Fonctionnalités du programme:

1)Saisir nom jouer

2)Plusieurs niveaux 

3)leader board

4)Application des instructions sur les listes 

5)Muli-joueur incomplet

6)timer

Dossiers:

-bin: les execut

-data: assets de  l'application

-obj: les .o

-doc: doxygen,power point presentation, diagramme de gantt, diagramme des modules 

src : 

	dossiers:
	
			main: fonctionnalités pour l'algorithme 
			
			sdl2: fonctionnalités sdl
			
			serveur: fonctionnalités pour server et la gestion des clients 
			
			socklib: fonctionnalités pour la connexion et l'acceptation client-server
			
			test: test regression 
			
			txt: verssion txt 
			
makefile 


