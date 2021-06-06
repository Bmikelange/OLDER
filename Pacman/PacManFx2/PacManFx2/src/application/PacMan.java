package application;

public class PacMan extends Entite {
	
	//deplace le pacman dans la direction choisit par l'utilisateur
	public void run()
	{	
		while(! cancel)
		{
			RealiserAction();
			try {
			      
	            Thread.sleep(vitesse);
	         }  catch (InterruptedException e) {
	         }
		}
	}
	
	//changes la position du pacman
	public int[] retNewPos(int tempPosx,int tempPosy)
	{
		int[] value=new int[2];
		switch (CurrentDirection) 
		{
			case Droite:
				tempPosy=tempPosy+1;
				break;
			case Gauche:
				tempPosy=tempPosy-1;
				break;
			case Bas:
				tempPosx=tempPosx+1;
				break;
			case Haut:
				tempPosx=tempPosx-1;
				break;
			case None:
				break;
		}
		value[0]=tempPosx;
		value[1]=tempPosy;
		return value;
	}
	
	//verifie si la position est autorisée
	public int verifierCase(int x,int y)
	{
		if(x==-1 || x==21)
		{
			return 1;
		}
		if(localTab[x][y].values==1)
		{
			return 0;
		}
		return 1;
	}	
	
	//valide les actions de déplacements
	public void RealiserAction()
	{
		int[] value=retNewPos(position_x, position_y);
		int i=verifierCase(value[1],value[0]);
		if(i ==1)
		{
			precedent_x=position_x;
			precedent_y=position_y;
			if(value[1]==-1)
			{
				value[1]=20;
			}
			if(value[1]==21)
			{
				value[1]=0;
			}
			position_x=value[0];
			position_y=value[1];
		}
	}
	
	//constructeur de pacman
	public PacMan(Direction dir,int posx,int posy,Case[][] tab)
	{
		super(dir,0,0,posx,posy,tab);
	}

}
