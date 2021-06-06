package application;

public class Fantome extends Entite {
	
	//genere une direction aleatoire et modifie la position du fantome
	public int[] aleaPos(int tempPosy,int tempPosx)
	{
		int[] value=new int[2];
		Direction dir = Direction.values()[(int)(Math.random()*Direction.values().length-1)];
		if (tempPosy==10 && (tempPosx==8 || tempPosx==9))
		{
			dir=Direction.Haut;
		}
		if (tempPosy==9 && tempPosx==9)
		{
			dir=Direction.Droite;
		}
		if (tempPosy==11 && tempPosx==9)
		{
			dir=Direction.Gauche;
		}
		if (tempPosy==10 && tempPosx==7)
		{
			dir= Direction.values()[(int)(Math.random()*(((Direction.values().length-1)/2)+1))];
		}
		CurrentDirection=dir;
		switch (dir) 
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
	
	//deplace le fantome toutes les vitesse milli seconde
	public void run()
	{	
		while(! cancel)
		{
			RealiserAction();
			try {  
	            Thread.sleep(vitesse) ;
	         }  catch (InterruptedException e) {
	         }
		}
	}
	
	//verifie si le deplacement est possible
	public int verifierCase(int x,int y,int precx,int precy)
	{
		if(y==precx && x==precy)
		{
			return 0;
		}
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
	
	//valide le deplacement
	public void RealiserAction()
	{
		int[] value=aleaPos(position_y, position_x);
		int i=0;
		while(verifierCase(value[1],value[0],precedent_x,precedent_y)==0)
		{
			value=aleaPos(position_y,position_x);
			if(i==50)
				break;
			i++;
		}
		if(i != 50)
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
	
	//le constructeur de fantome
	public Fantome(Direction dir,int posx,int posy,Case[][] tab)
	{
		super(dir,1,1,posx,posy,tab);
	}

}
