package application;

import java.util.ArrayList;
import java.util.Observable;
import java.io.FileReader;
import java.io.File;
import java.io.IOException;
import javafx.application.Platform;


public class Jeu extends Observable implements Runnable{

	// le plateau de jeu
	public Case[][] tableauJeu;
	
	//un tableau contenant toutes les entités
	public Entite[] tableauEntite;
	
	//le score réalisé par le joueur
	public int score;
	
	//un entier qui vérifie si le jeu est terminé
	public int Vic;
	
	//un booleen de controle du thread de jeu
	public boolean fin;
	
	//tableau des scores
	public  ArrayList<String[]> scoreTab;
	
	// initialise le jeu
    public void initialiser() throws IOException {
    	fin =false;
    	tableauJeu = new Case[21][21];
    	tableauEntite=new Entite[5];
    	Direction dir=Direction.None;
        int i, j;
        String currentWorkingPath = System.getProperty("user.dir");
        String fullPath = currentWorkingPath  + File.separator+"PacManFx2"+ File.separator+"data"+ File.separator+"map.txt" ;
        FileReader fr =
                new FileReader(fullPath);
        int n;
        i = 0; j = 0;
        while ((n=fr.read()) != -1) {
           
           
            if((char)n == '0') {
            	tableauJeu[j][i] = new Mur();
                j++;
            }
            if((char)n == '1') {
            	tableauJeu[j][i] = new Couloir(false,false); //couloir vide
                j++;
            }
            if((char)n == '2') {
            	tableauJeu[j][i] = new Couloir(true,false);
                j++;
            }
            if((char)n == '3') {
            	tableauJeu[j][i] = new Couloir(false,true);
                j++;
            }
            if(n == 13) { //code ascii du RETOUR CHARIOT
                i++;
                j = 0;
            }
               
           
        }
        
        fr.close();
        tableauEntite[0]=new PacMan(dir,15,10,tableauJeu);
        tableauEntite[1]=new Fantome(dir,9,9,tableauJeu);
        tableauEntite[2]=new Fantome(dir,9,10,tableauJeu);
        tableauEntite[3]=new Fantome(dir,8,10,tableauJeu);
        tableauEntite[4]=new Fantome(dir,9,11,tableauJeu);
        score=0;
	}
    
    public void initscoretab() throws IOException
    {
        scoreTab=Score.getScoreList();
    }
    
    
    //remets les donnees du jeu à leur etat de base a la fin de l'effet d'une super pac gomme
    public void game_res()
    {
    	for(int i=1;i<5;i++)
		{
			tableauEntite[i].vitesse=300;
		}
    	tableauEntite[0].immortal_object=0;
    }
    
    //set la direction de deplacement du pacman
    public void jeuPacman(Direction Dir)
    {
    	tableauEntite[0].CurrentDirection=Dir;
    }
    
    
    //verifie la victoire et notifie l'affichage qu'il doit changer
    public void run()
    {
    	while(!fin)
    	{
    		Vic=setPartie();
    		Platform.runLater(new Runnable()
    		{
    			@Override
    			public void run()
    			{
	    			setChanged();
	    			notifyObservers(this);
    			}
    		});
    		try {  
	            Thread.sleep(30);
	         }  catch (InterruptedException e) {
	         }
    	}
    }
    
    //lance les threads de chaque entite
    public void jeuFantome()
    {
    	tableauEntite[1].cancel=false;
    	tableauEntite[2].cancel=false;
    	tableauEntite[3].cancel=false;
    	tableauEntite[4].cancel=false;
    	tableauEntite[0].cancel=false;
    	Thread t0=new Thread(tableauEntite[0]);
    	Thread t1=new Thread(tableauEntite[1]);
    	Thread t2=new Thread(tableauEntite[2]);
    	Thread t3=new Thread(tableauEntite[3]);
    	Thread t4=new Thread(tableauEntite[4]);
    	t0.start();
    	t1.start();
    	t2.start();
    	t3.start();
    	t4.start();
    }
    
    //arretes les threads de chaque entite(en mettant a jour le booleen de controle)
    public void canceljeuFantome()
    {
    	for(int i=0;i<5;i++)
    	{
    		tableauEntite[i].cancel=true;
    	}
    }
	
    //verifie l'etat du jeu et set la victoire/defaite et les pacgommes, actualise le score
    public int setPartie()
	{
    	//verifie si le pacman est sur une pacgomme 
    	if(tableauJeu[tableauEntite[0].position_y][tableauEntite[0].position_x].PacGomme==true)
		{
    		tableauJeu[tableauEntite[0].position_y][tableauEntite[0].position_x].PacGomme=false;
    		score+=10;
		}
    	
    	//verifie si le pacman est sur une superpacgomme
		if(tableauJeu[tableauEntite[0].position_y][tableauEntite[0].position_x].SupPacGomme==true)
		{
			tableauEntite[0].immortal_object=1;
			tableauJeu[tableauEntite[0].position_y][tableauEntite[0].position_x].SupPacGomme=false;
			score+=10;
			return 3;
		}
		int i=0;
		
		//verifie si il reste des pacgommes
		for(int j=0;j<tableauJeu.length;j++)
		{
			for(int k=0;k<tableauJeu[j].length;k++)
			{
				if (tableauJeu[j][k].values==0)
				{
					int val =tableauJeu[j][k].PacGomme ? 1 : 0;
					int val2 =tableauJeu[j][k].SupPacGomme ? 1 : 0;
					i=i+val+val2;
					if(i != 0)
					{
						break;
					}
				}
				
			}
		}
		if(i==0)
		{
			return 1;
		}
		
		//colisions fantome/pacman si pas de superpacgommes
		if(tableauEntite[0].immortal_object==0)
		{	
			for(int j=1;j<5;j++)
			{
				if((tableauEntite[0].position_x==tableauEntite[j].precedent_x &&
				   tableauEntite[0].position_y==tableauEntite[j].precedent_y &&
				   tableauEntite[0].precedent_x==tableauEntite[j].position_x &&
				   tableauEntite[0].precedent_y==tableauEntite[j].position_y) ||
				   (tableauEntite[0].position_x==tableauEntite[j].position_x &&
					tableauEntite[0].position_y==tableauEntite[j].position_y))
				{
					return 2;
				}
			}
		}
		
		//colisions fantome/pacman si superpacgommes
		if(tableauEntite[0].immortal_object==1)
		{	
			for(int j=1;j<5;j++)
			{
				if((tableauEntite[0].position_x==tableauEntite[j].precedent_x &&
				   tableauEntite[0].position_y==tableauEntite[j].precedent_y &&
				   tableauEntite[0].precedent_x==tableauEntite[j].position_x &&
				   tableauEntite[0].precedent_y==tableauEntite[j].position_y) ||
				   (tableauEntite[0].position_x==tableauEntite[j].position_x &&
					tableauEntite[0].position_y==tableauEntite[j].position_y))
				{
					tableauEntite[j].position_x=9;
					tableauEntite[j].position_y=10;
					tableauEntite[j].precedent_x=0;
					tableauEntite[j].precedent_y=0;
					score+=200;
				}
			}
		}
    	return 0;
	}


    //genere un niveau aleatoire
	public void niveau_aleatoire()
	{
		//rempli les cotés de murs
		tableauJeu=new Case[21][21];
		for(int i=0;i<21;i++)
		{
			tableauJeu[0][i]=new Mur();
			tableauJeu[i][0]=new Mur();
			tableauJeu[20][i]=new Mur();
			tableauJeu[i][20]=new Mur();
		}
		//rempli le plateau de maniere aleatoire
		for(int i=1;i<20;i++)
		{
			for(int j=1;j<20;j++)
			{
				int rand=(int)(Math.random()*40);
				if(rand>=25 && rand<30)
				{
					tableauJeu[i][j]=new Couloir(false,false);
				}
				if(rand<25)
				{
					tableauJeu[i][j]=new Mur();
				}
				if(rand >=30)
				{
					tableauJeu[i][j]=new Couloir(true,false);
				}
			}
		}
		
		//force certaine case en couloir
		tableauJeu[3][3]=new Couloir(false,true);
		tableauJeu[17][3]=new Couloir(false,true);
		tableauJeu[3][17]=new Couloir(false,true);
		tableauJeu[17][17]=new Couloir(false,true);
		tableauJeu[10][15]=new Couloir(false,false);
		tableauJeu[10][7]=new Couloir(false,false);
		tableauJeu[11][7]=new Couloir(false,false);
		tableauJeu[10][6]=new Couloir(false,false);
		
		//verifie que chaque couloir est adjacent a deux autres couloirs, 
		//si ce n'est pas le cas crée un nouveau couloir relié au premier 
		//et reverifie toute la grille
		for(int i=1;i<20;i++)
		{
			for(int j=1;j<20;j++)
			{
				if(tableauJeu[i][j] instanceof Couloir)
				{
					if(!(((tableauJeu[i-1][j] instanceof Couloir) && (tableauJeu[i+1][j] instanceof Couloir)) ||
						 ((tableauJeu[i-1][j] instanceof Couloir) && (tableauJeu[i][j+1] instanceof Couloir)) ||
						 ((tableauJeu[i-1][j] instanceof Couloir) && (tableauJeu[i][j-1] instanceof Couloir)) ||
						 ((tableauJeu[i][j-1] instanceof Couloir) && (tableauJeu[i+1][j] instanceof Couloir)) ||
						 ((tableauJeu[i][j+1] instanceof Couloir) && (tableauJeu[i+1][j] instanceof Couloir)) ||
						 ((tableauJeu[i][j-1] instanceof Couloir) && (tableauJeu[i][j+1] instanceof Couloir)) ))
					{

						if((tableauJeu[i-1][j] instanceof Mur) &&(i-1>0))
						{
							tableauJeu[i-1][j]=new Couloir(true,false);
						}
						else if((tableauJeu[i+1][j] instanceof Mur) && (i+1<20))
							{
								tableauJeu[i+1][j]=new Couloir(true,false);
							}
							else if((tableauJeu[i][j+1] instanceof Mur) && (j+1<20))
								{
									tableauJeu[i][j+1]=new Couloir(true,false);
								}
								else if((tableauJeu[i][j-1] instanceof Mur) && (j-1>0))
									{
										tableauJeu[i][j-1]=new Couloir(true,false);
									}
						j=0;
						i=0;
					}
				}
			}
		}
		
		//force certaines case en couloir
		tableauJeu[9][9]=new Couloir(false,false);
		tableauJeu[10][9]=new Couloir(false,false);
		tableauJeu[11][9]=new Couloir(false,false);
		tableauJeu[10][8]=new Couloir(false,false);
		tableauJeu[0][10]=new Couloir(false,false);
		tableauJeu[20][10]=new Couloir(false,false);
		tableauJeu[1][10]=new Couloir(false,false);
		tableauJeu[19][10]=new Couloir(false,false);
		
		tableauEntite[0]=new PacMan(Direction.None,15,10,tableauJeu);
        tableauEntite[1]=new Fantome(Direction.None,9,9,tableauJeu);
        tableauEntite[2]=new Fantome(Direction.None,9,10,tableauJeu);
        tableauEntite[3]=new Fantome(Direction.None,8,10,tableauJeu);
        tableauEntite[4]=new Fantome(Direction.None,9,11,tableauJeu);
        score=0;
		
	}
}
